"""
E-Net 脑肿瘤分割训练(kaggle_3m 数据集)
  模型保存在 ./checkpoints/best_enet.pth
  训练结束后生成可视化分割结果（保存在 ./results 文件夹）
  训练记录保存为 ./results/training_history.csv
"""

# ==================== 1. 导入必要的库 ====================
import os
os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE"

import glob
import re
import random
import argparse
import time
import csv
import numpy as np
from PIL import Image
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
import torch.optim as optim
import torchvision.transforms.functional as TF

#------------------------------------------实验2-01：导入ENet模型类--------------------------------------------
#提示：在models文件下
from models.enet import ENet                                    #在此填空


# ==================== 2. 数据集类定义 ====================
class BrainTumorDataset(Dataset):
    def __init__(self, root_dir, target_size=(512, 512), augment=False, num_classes=2):
        self.root_dir = root_dir
        self.target_size = target_size
        self.augment = augment
        self.num_classes = num_classes
        self.samples = []
        self.need_map = False

        # 收集所有 (图像, 标签) 对
        patient_dirs = [d for d in glob.glob(os.path.join(root_dir, "*")) if os.path.isdir(d)]
        if not patient_dirs:
            raise RuntimeError(f"在 {root_dir} 下未找到任何病人文件夹，请检查路径。")

        for patient_dir in patient_dirs:
            all_tifs = glob.glob(os.path.join(patient_dir, "*.tif"))
            for tif_path in all_tifs:
                basename = os.path.basename(tif_path)

                # ------------------------------------------实验2-02：数据集类初始化中的路径收集------------------------------------------
                # 提示：只处理图像文件（非mask），并找到对应的mask文件
                if not basename.endswith("_mask.tif") and re.search(r'_\d+\.tif$', basename):
                    # 提示：将图像文件名中的".tif"替换为"_mask.tif"
                    mask_basename =  basename.replace(".tif", "_mask.tif")                                        #在此填空

                    mask_path = os.path.join(patient_dir, mask_basename)
                    if os.path.exists(mask_path):
                        self.samples.append((tif_path, mask_path))

        print(f"成功加载 {len(self.samples)} 对图像-标签。")

        # 预先扫描所有 mask，确定是否需要映射
        print("正在检查标签格式...")
        need_map = False
        invalid_count = 0
        for _, mask_path in self.samples:
            mask = Image.open(mask_path).convert("L")
            mask_np = np.array(mask)
            uniq = np.unique(mask_np)
            if np.any(uniq > 1):
                need_map = True
                invalid_count += 1
        if need_map:
            print(f"检测到 {invalid_count} 个 mask 文件包含大于1的像素值（通常为255），")
            print("训练时将自动将非零值映射为1（肿瘤类别）。")
            self.need_map = True
        else:
            print("所有 mask 标签值已符合要求（0/1格式）。")

    def __len__(self):
        return len(self.samples)

    def __getitem__(self, idx):
        img_path, mask_path = self.samples[idx]

        image = Image.open(img_path).convert("RGB")
        mask = Image.open(mask_path).convert("L")

        image = image.resize(self.target_size, Image.BILINEAR)
        mask = mask.resize(self.target_size, Image.NEAREST)

        image_np = np.array(image, dtype=np.float32) / 255.0
        mask_np = np.array(mask, dtype=np.int64)

        # 映射 255 -> 1
        if self.need_map:
            mask_np = (mask_np > 0).astype(np.int64)

        # 二次保险：裁剪超出范围的值
        mask_np = np.clip(mask_np, 0, self.num_classes - 1)

        # 数据增强
        if self.augment:
            if random.random() > 0.5:
                image_np = np.fliplr(image_np).copy()
                mask_np = np.fliplr(mask_np).copy()
            if random.random() > 0.5:
                image_np = np.flipud(image_np).copy()
                mask_np = np.flipud(mask_np).copy()
            if random.random() > 0.5:
                angle = random.uniform(-10, 10)
                img_pil = Image.fromarray((image_np * 255).astype(np.uint8))
                mask_pil = Image.fromarray(mask_np.astype(np.uint8))
                img_pil = TF.rotate(img_pil, angle, interpolation=Image.BILINEAR)
                mask_pil = TF.rotate(mask_pil, angle, interpolation=Image.NEAREST)
                image_np = np.array(img_pil, dtype=np.float32) / 255.0
                mask_np = np.array(mask_pil, dtype=np.int64)

        image_tensor = torch.from_numpy(image_np).permute(2, 0, 1).float()
        mask_tensor = torch.from_numpy(mask_np).long()
        return image_tensor, mask_tensor


# ==================== 3. 损失函数定义 ====================
class DiceLoss(nn.Module):
    def __init__(self, smooth=1e-6):
        super().__init__()
        self.smooth = smooth

    def forward(self, pred, target):
        pred_softmax = F.softmax(pred, dim=1)
        target_one_hot = F.one_hot(target, num_classes=pred.shape[1]).permute(0, 3, 1, 2).float()
        dims = (2, 3)
        intersection = (pred_softmax * target_one_hot).sum(dim=dims)
        union = pred_softmax.sum(dim=dims) + target_one_hot.sum(dim=dims)
        dice = (2.0 * intersection + self.smooth) / (union + self.smooth)
        return 1 - dice.mean()

class CombinedLoss(nn.Module):
    def __init__(self, ce_weight=1.0, dice_weight=1.0, class_weights=None):
        super().__init__()
        self.ce_weight = ce_weight
        self.dice_weight = dice_weight
        self.ce = nn.CrossEntropyLoss(weight=class_weights)
        self.dice = DiceLoss()

    def forward(self, pred, target):
        ce_loss = self.ce(pred, target)
        dice_loss = self.dice(pred, target)

        #------------------------------------------实验2-03：损失函数的组合方式------------------------------------------
        # 提示：将两个损失按权重组合  ce_loss * ce_weight + dice_loss * dice_weight
        return self.ce_weight * ce_loss + self.dice_weight * dice_loss                                                            #在此填空


# ==================== 4. 评估指标：Dice 系数（类别平均） ====================
class DiceMetric:
    def __init__(self, num_classes):
        self.num_classes = num_classes
        self.reset()

    def reset(self):
        self.total_dice = 0.0
        self.count = 0

    def add(self, outputs, labels):
        preds = outputs.argmax(dim=1)
        for c in range(self.num_classes):
            pred_c = (preds == c).float()
            label_c = (labels == c).float()
            intersection = (pred_c * label_c).sum()
            union = pred_c.sum() + label_c.sum()
            dice = (2.0 * intersection) / (union + 1e-6)
            self.total_dice += dice.item()
            self.count += 1

    def value(self):
        return self.total_dice / self.count if self.count > 0 else 0.0


# ==================== 5. 可视化函数 ====================
def visualize_predictions(model, dataloader, device, num_classes, save_dir, num_samples=4):
    """
    从 dataloader 中随机抽取 num_samples 张图片，显示原图、真实 mask、预测 mask
    """
    model.eval()
    os.makedirs(save_dir, exist_ok=True)

    # 随机抽取几个样本
    indices = random.sample(range(len(dataloader.dataset)), min(num_samples, len(dataloader.dataset)))
    fig, axes = plt.subplots(num_samples, 3, figsize=(12, 4 * num_samples))
    if num_samples == 1:
        axes = axes.reshape(1, -1)

    for i, idx in enumerate(indices):
        image, mask = dataloader.dataset[idx]
        image = image.unsqueeze(0).to(device)   # (1,3,H,W)
        mask = mask.cpu().numpy()

        with torch.no_grad():
            output = model(image)
            pred = output.argmax(dim=1).squeeze(0).cpu().numpy()

        # 图像转回 HWC 并显示
        img_np = image.squeeze(0).cpu().numpy().transpose(1, 2, 0)

        axes[i, 0].imshow(img_np)
        axes[i, 0].set_title("Original Image")
        axes[i, 0].axis("off")

        axes[i, 1].imshow(mask, cmap="gray")
        axes[i, 1].set_title("Ground Truth Mask")
        axes[i, 1].axis("off")

        axes[i, 2].imshow(pred, cmap="gray")
        axes[i, 2].set_title("Predicted Mask")
        axes[i, 2].axis("off")

    plt.tight_layout()
    save_path = os.path.join(save_dir, "segmentation_results.png")
    plt.savefig(save_path, dpi=150)
    print(f"可视化结果已保存至: {save_path}")
    plt.close()


# ==================== 6. 主训练函数 ====================
def main(args):
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    #device = torch.device("cpu")
    print(f"使用设备: {device}")

    num_classes = args.num_classes
    batch_size = args.batch_size
    epochs = args.epochs
    learning_rate = args.lr
    target_size = (args.img_size, args.img_size)
    data_root = args.data_root

    # 创建保存训练日志的目录
    results_dir = "./results"
    os.makedirs(results_dir, exist_ok=True)
    log_path = os.path.join(results_dir, "training_history.csv")

    # 创建数据集（训练集启用增强）
    full_dataset = BrainTumorDataset(
        root_dir=data_root,
        target_size=target_size,
        augment=True,
        num_classes=num_classes
    )

    # 划分训练/验证集
    val_ratio = args.val_ratio
    val_size = int(len(full_dataset) * val_ratio)
    train_size = len(full_dataset) - val_size
    train_dataset, val_dataset = torch.utils.data.random_split(
        full_dataset, [train_size, val_size],
        generator=torch.Generator().manual_seed(42)
    )

    # 验证集不需要增强
    original_augment = full_dataset.augment
    full_dataset.augment = False
    val_dataset_no_aug = torch.utils.data.Subset(full_dataset, val_dataset.indices)
    full_dataset.augment = original_augment

    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=0)  # CPU训练建议 num_workers=0
    val_loader = DataLoader(val_dataset_no_aug, batch_size=batch_size, shuffle=False, num_workers=0)

    print(f"训练集大小: {len(train_dataset)}, 验证集大小: {len(val_dataset)}")

    # 模型
    model = ENet(num_classes=num_classes, encoder_relu=False, decoder_relu=True)
    model = model.to(device)

    # 损失函数
    class_weights = None
    if num_classes == 2:
        class_weights = torch.tensor([1.0, 2.0]).to(device)
    criterion = CombinedLoss(ce_weight=1.0, dice_weight=1.0, class_weights=class_weights)

    optimizer = optim.Adam(model.parameters(), lr=learning_rate)
    scheduler = optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode='min', factor=0.5, patience=10)

    train_metric = DiceMetric(num_classes)
    val_metric = DiceMetric(num_classes)

    best_val_dice = 0.0
    os.makedirs(args.save_dir, exist_ok=True)

    # ---------- 准备CSV日志文件，写入表头 ----------
    with open(log_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['Epoch', 'Train Loss', 'Train Dice', 'Val Loss', 'Val Dice', 'Best Val Dice'])

    start_time = time.time()
    print("开始训练...")
    for epoch in range(1, epochs + 1):
        # ---------- 训练阶段 ----------
        model.train()
        train_loss = 0.0
        train_metric.reset()
        for images, masks in train_loader:
            images, masks = images.to(device), masks.to(device)
            optimizer.zero_grad()
            outputs = model(images)
            loss = criterion(outputs, masks)
            loss.backward()
            optimizer.step()
            train_loss += loss.item()
            train_metric.add(outputs.detach(), masks.detach())

        avg_train_loss = train_loss / len(train_loader)
        train_dice = train_metric.value()

        # ---------- 验证阶段 ----------
        model.eval()
        val_loss = 0.0
        val_metric.reset()
        with torch.no_grad():
            for images, masks in val_loader:
                images, masks = images.to(device), masks.to(device)
                outputs = model(images)
                loss = criterion(outputs, masks)
                val_loss += loss.item()
                val_metric.add(outputs, masks)

        avg_val_loss = val_loss / len(val_loader)
        val_dice = val_metric.value()

        # 调整学习率
        scheduler.step(avg_val_loss)

        # 打印日志
        print(f"Epoch {epoch:3d}/{epochs} | "
              f"Train Loss: {avg_train_loss:.4f} | Train Dice: {train_dice:.4f} | "
              f"Val Loss: {avg_val_loss:.4f} | Val Dice: {val_dice:.4f}")

        # 保存最佳模型
        if val_dice > best_val_dice:
            best_val_dice = val_dice
            torch.save(model.state_dict(), os.path.join(args.save_dir, "best_enet.pth"))
            print(f"  -> 保存最佳模型，Dice = {val_dice:.4f}")

        # ---------- 将当前epoch的记录写入CSV ----------
        with open(log_path, 'a', newline='') as f:
            writer = csv.writer(f)
            writer.writerow([epoch, avg_train_loss, train_dice, avg_val_loss, val_dice, best_val_dice])

    end_time = time.time()
    elapsed = end_time - start_time
    elapsed_min = elapsed / 60
    print(f"\n训练完成！总耗时: {elapsed:.2f} 秒 ({elapsed_min:.2f} 分钟)")
    print(f"训练记录已保存至: {log_path}")

    # -------------------- 训练结束后可视化 --------------------
    print("\n正在生成分割结果可视化...")
    best_model_path = os.path.join(args.save_dir, "best_enet.pth")
    if os.path.exists(best_model_path):
        model.load_state_dict(torch.load(best_model_path, map_location=device))
        print(f"加载最佳模型: {best_model_path}")
    else:
        print("未找到最佳模型，使用当前模型进行可视化。")

    visualize_predictions(
        model=model,
        dataloader=val_loader,
        device=device,
        num_classes=num_classes,
        save_dir="./results",
        num_samples=4
    )
    print("可视化完成。")

#------------------------------------------实验3：调整超参数（学习率、批次大小等），使验证集Dice系数达到0.7以上------------------------------------------
# ==================== 7. 命令行参数解析与入口 ====================
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="ENet 脑肿瘤分割训练")
    parser.add_argument("--data_root", type=str, default="./data/kaggle_3m", help="kaggle_3m 数据集的根目录")
    parser.add_argument("--num_classes", type=int, default=2, help="分割类别数（包括背景）")
    parser.add_argument("--batch_size", type=int, default=16, help="批次大小")
    parser.add_argument("--epochs", type=int, default=3, help="训练轮数")
    parser.add_argument("--lr", type=float, default=0.0001, help="学习率")
    parser.add_argument("--img_size", type=int, default=512, help="输入图像大小（正方形）")
    parser.add_argument("--val_ratio", type=float, default=0.2, help="验证集比例")
    parser.add_argument("--save_dir", type=str, default="./checkpoints", help="模型保存目录")
    args = parser.parse_args()

    main(args)