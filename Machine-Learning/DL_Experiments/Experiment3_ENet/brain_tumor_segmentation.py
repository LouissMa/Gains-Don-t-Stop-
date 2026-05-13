"""
单张图片脑肿瘤分割预测
运行后自动弹出文件选择窗口，选择图片即可展示分割结果
"""

import os

# 解决 OpenMP 冲突（必须在导入其他库之前设置）
os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE"

import tkinter as tk
from tkinter import filedialog
import numpy as np
from PIL import Image
import matplotlib

matplotlib.use('TkAgg')  # 使用交互式后端，确保弹窗显示
import matplotlib.pyplot as plt
import torch

from models.enet import ENet


def select_file(title="请选择图片文件",
                filetypes=[("图片文件", "*.tif *.tiff *.png *.jpg *.jpeg"), ("所有文件", "*.*")]):
    """
    弹出文件选择对话框，返回选中的文件路径
    """
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口
    root.attributes('-topmost', True)  # 窗口置顶
    file_path = filedialog.askopenfilename(title=title, filetypes=filetypes)
    root.destroy()
    return file_path


def predict_and_show(model, image_path, mask_path=None, img_size=512, device='cpu'):
    """
    对单张图片进行分割预测并展示结果
    """
    device = torch.device(device)
    model = model.to(device)
    model.eval()

    # 加载图像
    image = Image.open(image_path).convert("RGB")
    original_image = image.copy()
    image_resized = image.resize((img_size, img_size), Image.BILINEAR)
    image_np = np.array(image_resized, dtype=np.float32) / 255.0
    image_tensor = torch.from_numpy(image_np).permute(2, 0, 1).unsqueeze(0).float().to(device)

    # 预测
    with torch.no_grad():
        output = model(image_tensor)
        pred = output.argmax(dim=1).squeeze(0).cpu().numpy()

    # 加载真实掩码
    mask_true = None
    if mask_path and os.path.exists(mask_path):
        mask = Image.open(mask_path).convert("L")
        mask_resized = mask.resize((img_size, img_size), Image.NEAREST)
        mask_np = np.array(mask_resized, dtype=np.int64)
        if mask_np.max() > 1:
            mask_np = (mask_np > 0).astype(np.int64)
        mask_true = mask_np

    # 展示结果
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))

    axes[0].imshow(original_image)
    axes[0].set_title("Original Image")
    axes[0].axis("off")

    if mask_true is not None:
        axes[1].imshow(mask_true, cmap="gray")
        axes[1].set_title("Ground Truth Mask")
    else:
        axes[1].text(0.5, 0.5, "No Mask Provided", ha='center', va='center', fontsize=12)
        axes[1].set_title("Ground Truth Mask")
    axes[1].axis("off")

    axes[2].imshow(pred, cmap="gray")
    axes[2].set_title("Predicted Mask")
    axes[2].axis("off")

    plt.tight_layout()
    plt.show()


def load_model(model_path, num_classes=2, device='cpu'):
    """
    加载训练好的模型
    """
    print(f"加载模型: {model_path}")
    model = ENet(num_classes=num_classes, encoder_relu=False, decoder_relu=True)
    state_dict = torch.load(model_path, map_location=device)
    model.load_state_dict(state_dict)
    return model


def main():
    print("=" * 50)
    print("ENet 脑肿瘤分割预测")
    print("=" * 50)

    # 模型路径（可修改为你的模型路径）
    model_path = "./checkpoints/best_enet.pth"
    if not os.path.exists(model_path):
        print(f"模型文件不存在: {model_path}")
        print("请先训练模型，或将模型文件放置在正确位置")
        return

    # 选择设备
    device = "cuda" if torch.cuda.is_available() else "cpu"
    print(f"使用设备: {device}")

    # 加载模型
    model = load_model(model_path, num_classes=2, device=device)

    # 选择图片
    print("\n请选择要预测的图片...")
    image_path = select_file(title="请选择脑肿瘤MRI图像",
                             filetypes=[("图片文件", "*.tif *.tiff *.png *.jpg *.jpeg"), ("所有文件", "*.*")])
    if not image_path:
        print("未选择任何图片，程序退出")
        return
    print(f"已选择图片: {image_path}")

    # 是否选择对应的掩码（可选）
    use_mask = input("\n是否同时展示真实掩码？(y/n，默认n): ").strip().lower()
    mask_path = None
    if use_mask == 'y' or use_mask == 'yes':
        print("请选择对应的真实掩码图片...")
        mask_path = select_file(title="请选择真实掩码",
                                filetypes=[("图片文件", "*.tif *.tiff *.png *.jpg *.jpeg"), ("所有文件", "*.*")])
        if mask_path:
            print(f"已选择掩码: {mask_path}")
        else:
            print("未选择掩码，将只展示预测结果")

    # 预测并展示
    print("\n正在预测，请稍候...")
    predict_and_show(model, image_path, mask_path, img_size=512, device=device)
    print("预测完成！")


if __name__ == "__main__":
    main()