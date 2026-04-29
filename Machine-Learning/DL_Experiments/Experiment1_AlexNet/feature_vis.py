import torch
import torch.nn as nn
from torchvision import datasets, transforms
import matplotlib.pyplot as plt
import os
# 防止matplotlib弹窗报错
os.environ['KMP_DUPLICATE_LIB_OK'] = 'TRUE'

# ------------------------- 重新定义模型结构以加载权重 -------------------------
class AlexNetMNIST(nn.Module):
    def __init__(self, num_classes=10):
        super(AlexNetMNIST, self).__init__()
        self.features = nn.Sequential(
            nn.Conv2d(1, 32, kernel_size=5, stride=1, padding=2), # features[0]: 第一层卷积
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(32, 64, kernel_size=5, padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(64, 128, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(128, 128, kernel_size=3, padding=1),        # features[8]: 第四层卷积
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=2, stride=2),
        )
        self.classifier = nn.Sequential(
            nn.Dropout(0.5),
            nn.Linear(1152, 512),
            nn.ReLU(inplace=True),
            nn.Dropout(0.5),
            nn.Linear(512, 256),
            nn.ReLU(inplace=True),
            nn.Linear(256, num_classes),
        )

# ------------------------- 可视化函数 -------------------------
def main():
    device = torch.device("cpu")
    model = AlexNetMNIST(num_classes=10).to(device)
    
    # 1. 加载已训练的模型权重
    model_path = './models/alexnet_mnist.pth'
    if not os.path.exists(model_path):
        print(f"找不到模型文件 {model_path}，请先运行 AlexNet.py 训练模型！")
        return
    model.load_state_dict(torch.load(model_path, map_location=device))
    model.eval()

    # 2. 加载一张测试集图片
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])
    test_dataset = datasets.MNIST(root='./data', train=False, download=True, transform=transform)
    
    # 获取第一张图片 (你可以改 [0] 里的数字换其他图片)
    image_tensor, label = test_dataset[0] 
    image_tensor = image_tensor.unsqueeze(0) # 增加 batch 维度: [1, 1, 28, 28]

    # 3. 提取特征图
    # 第一层卷积的输出 (索引为0)
    conv1_output = model.features[0](image_tensor)
    
    # 第四层卷积的输出 (需依次经过前面的层，第四层卷积的索引为8)
    x = image_tensor
    for i in range(9):
        x = model.features[i](x)
    conv4_output = x

    # 4. 绘图函数
    def plot_feature_maps(feature_map_tensor, title):
        # 转换为 numpy 格式并取前10个通道
        fmaps = feature_map_tensor[0, :10].detach().numpy() 
        plt.figure(figsize=(12, 5))
        plt.suptitle(title, fontsize=16)
        for i in range(10):
            plt.subplot(2, 5, i + 1)
            plt.imshow(fmaps[i], cmap='viridis') # 使用 viridis 伪彩色更容易观察
            plt.axis('off')
            plt.title(f'Map {i+1}')
        plt.tight_layout()
        plt.show()

    # 显示原图
    plt.figure(figsize=(3,3))
    plt.imshow(image_tensor.squeeze().numpy(), cmap='gray')
    plt.title(f"Original Image (Label: {label})")
    plt.axis('off')
    plt.show()

    # 绘制并展示前10个特征图
    plot_feature_maps(conv1_output, "Conv1 Layer - First 10 Feature Maps")
    plot_feature_maps(conv4_output, "Conv4 Layer - First 10 Feature Maps")

if __name__ == '__main__':
    main()