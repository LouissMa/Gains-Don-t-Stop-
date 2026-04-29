import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
import time
import os


# ------------------------- 简化版AlexNet模型 -------------------------
#实验题01-04： 构造网络模型代码补全
class AlexNetMNIST(nn.Module):
    def __init__(self, num_classes=10):
        super(AlexNetMNIST, self).__init__()
        # 输入 1x28x28
        self.features = nn.Sequential(
            nn.Conv2d(1, 32, kernel_size=5, stride=1, padding=2),# 空7：输入通道数，MNIST为单通道灰度图
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),  # 输出 32x13x13

            nn.Conv2d(32, 64, kernel_size=5, padding=2), # 空8：该层将通道数从32扩展到64，是特征提取的重要步骤
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),  # 输出 64x6x6

            nn.Conv2d(64, 128, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(128, 128, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=2, stride=2),  # 输出 128x3x3
        )
        self.classifier = nn.Sequential(
            nn.Dropout(0.5),# 空9：Dropout层，以0.5的概率随机丢弃神经元，防止过拟合
            nn.Linear(1152, 512),# 空10： 此处是展平后的特征向量长度，由128通道、3x3空间尺寸决定
            nn.ReLU(inplace=True),
            nn.Dropout(0.5),
            nn.Linear(512, 256),
            nn.ReLU(inplace=True),
            nn.Linear(256, num_classes),
        )

    def forward(self, x):
        x = self.features(x)
        x = x.view(x.size(0), -1)
        x = self.classifier(x)
        return x


# ------------------------- 训练函数 -------------------------
def train(model, device, train_loader, optimizer, criterion, epoch):
    model.train()
    total_loss = 0
    correct = 0
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        output = model(data)
        loss = criterion(output, target)
        loss.backward()
        optimizer.step()

        total_loss += loss.item()
        pred = output.argmax(dim=1, keepdim=True)
        correct += pred.eq(target.view_as(pred)).sum().item()

        if batch_idx % 50 == 0:
            print(f'Train Epoch: {epoch} [{batch_idx * len(data)}/{len(train_loader.dataset)} '
                  f'({100. * batch_idx / len(train_loader):.0f}%)]\tLoss: {loss.item():.6f}')

    avg_loss = total_loss / len(train_loader)
    acc = 100. * correct / len(train_loader.dataset)
    print(f'Epoch {epoch} finished. Average loss: {avg_loss:.6f}, Accuracy: {acc:.2f}%')
    return avg_loss, acc


# ------------------------- 测试函数 -------------------------
def test(model, device, test_loader, criterion):
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += criterion(output, target).item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()

    test_loss /= len(test_loader)
    acc = 100. * correct / len(test_loader.dataset)
    print(f'\nTest set: Average loss: {test_loss:.6f}, Accuracy: {acc:.2f}%\n')
    return test_loss, acc


# ------------------------- 主程序（菜单） -------------------------
def main():
    print("=" * 50)
    print("AlexNet (简化版) 手写数字识别 (MNIST)")
    print("=" * 50)

    # 菜单：设置超参数
    #运行代码，键盘输入训练超参
    epochs = int(input("请输入训练轮数 (建议5、10轮，默认5轮): ") or 5)
    lr = float(input("请输入学习率 (建议0.01、0.001，默认0.01): ") or 0.01)
    batch_size = int(input("请输入批大小 (默认64，可以是32、128等): ") or 64)
    print("使用 CPU 进行训练...")
    device = torch.device("cpu")

    # 数据预处理：只标准化，不缩放（28x28直接输入）
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])

    # 使用本地数据集 'data_mnist'
    # 使用本地数据集 'data_mnist'
    # 修改路径为 ./data
    data_root = './data'
    
    # 记得把 download=False 改成 download=True
    train_dataset = datasets.MNIST(root=data_root, train=True, download=True, transform=transform)
    test_dataset = datasets.MNIST(root=data_root, train=False, download=True, transform=transform)

    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

    # 初始化模型、损失函数、优化器
    model = AlexNetMNIST(num_classes=10).to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=lr)

    print(f"\n开始训练 (epochs={epochs}, lr={lr}, batch_size={batch_size})")
    start_time = time.time()

    for epoch in range(1, epochs + 1):
        train_loss, train_acc = train(model, device, train_loader, optimizer, criterion, epoch)
        test_loss, test_acc = test(model, device, test_loader, criterion)

    elapsed = time.time() - start_time
    print(f"训练完成！总耗时: {elapsed:.2f} 秒 ({elapsed / 60:.2f} 分钟)")

    # 保存模型
    os.makedirs('./models', exist_ok=True)
    model_path = './models/alexnet_mnist.pth'
    torch.save(model.state_dict(), model_path)
    print(f"模型已保存到: {model_path}")


if __name__ == "__main__":
    main()
