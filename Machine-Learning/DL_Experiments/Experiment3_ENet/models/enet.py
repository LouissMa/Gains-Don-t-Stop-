#ENet（Efficient Neural Network），一个用于实时语义分割的深度学习模型。

# ENet 的核心是 Bottleneck 模块，分为三种：
# RegularBottleneck：保持分辨率，提取特征
# DownsamplingBottleneck：降低分辨率，扩大感受野，保存池化索引用于上采样
# UpsamplingBottleneck：恢复分辨率，利用保存的索引进行上采样

# 整个网络结构像字母 V：先下采样（编码器），后上采样（解码器）。

import torch.nn as nn
import torch


class InitialBlock(nn.Module):
    """初始块：并行使用卷积和池化，下采样的同时扩充通道数"""

    def __init__(self,
                 in_channels,
                 out_channels,
                 bias=False,
                 relu=True):
        super().__init__()

        if relu:
            activation = nn.ReLU
        else:
            activation = nn.PReLU

        # 主分支：普通卷积（输出通道 = 总通道 - 3）
        self.main_branch = nn.Conv2d(
            in_channels,
            #------------------------------------------实验1-01：InitialBlock的通道数计算------------------------------------------
            #提示：已知总输出通道为 out_channels，扩展分支贡献3个通道。那么主分支应该贡献多少？请填写表达式。
            out_channels - 3,
            kernel_size=3,
            stride=2,
            padding=1,
            bias=bias)

        # 扩展分支：最大池化（输出3个通道）
        self.ext_branch = nn.MaxPool2d(3, stride=2, padding=1)
        # 初始化用于拼接之后的批量归一化
        self.batch_norm = nn.BatchNorm2d(out_channels)
        # 拼接分支后应用的 PReLU 层
        self.out_activation = activation()

    def forward(self, x):
        main = self.main_branch(x)
        ext = self.ext_branch(x)

        # 合并分支
        out = torch.cat((main, ext), 1)

        # 应用批量归一化
        out = self.batch_norm(out)

        return self.out_activation(out)

# ========== 核心部分1：普通瓶颈（保持分辨率） ==========
class RegularBottleneck(nn.Module):
    """RegularBottleneck: 主分支 = 恒等映射，扩展分支 = 1x1降维 -> 卷积 -> 1x1升维 -> Dropout
           最终输出 = 主分支 + 扩展分支（残差连接）"""

    def __init__(self,
                 channels,
                 internal_ratio=4,
                 kernel_size=3,
                 padding=0,
                 dilation=1,
                 asymmetric=False,
                 dropout_prob=0,
                 bias=False,
                 relu=True):
        super().__init__()

        # 检查内部“scale”参数是否在预期范围内
        # [1， 通道数]
        if internal_ratio <= 1 or internal_ratio > channels:
            raise RuntimeError("Value out of range. Expected value in the "
                               "interval [1, {0}], got internal_scale={1}."
                               .format(channels, internal_ratio))

        internal_channels = channels // internal_ratio

        if relu:
            activation = nn.ReLU
        else:
            activation = nn.PReLU

        # Main branch - shortcut connection

        # Extension branch - 1x1 convolution, followed by a regular, dilated or
        # asymmetric convolution, followed by another 1x1 convolution, and,
        # finally, a regularizer (spatial dropout). Number of channels is constant.

        # 扩展分支：1x1降维
        self.ext_conv1 = nn.Sequential(
            nn.Conv2d(
                channels,
                internal_channels,
                kernel_size=1,
                stride=1,
                bias=bias), nn.BatchNorm2d(internal_channels), activation())

        # If the convolution is asymmetric we split the main convolution in
        # two. Eg. for a 5x5 asymmetric convolution we have two convolution:
        # the first is 5x1 and the second is 1x5.
        # 中间卷积（可选：非对称卷积）
        if asymmetric:
            self.ext_conv2 = nn.Sequential(
                nn.Conv2d(
                    internal_channels,
                    internal_channels,
                    kernel_size=(kernel_size, 1),
                    stride=1,
                    padding=(padding, 0),
                    dilation=dilation,
                    bias=bias), nn.BatchNorm2d(internal_channels), activation(),
                nn.Conv2d(
                    internal_channels,
                    internal_channels,
                    kernel_size=(1, kernel_size),
                    stride=1,
                    padding=(0, padding),
                    dilation=dilation,
                    bias=bias), nn.BatchNorm2d(internal_channels), activation())
        else:
            self.ext_conv2 = nn.Sequential(
                nn.Conv2d(
                    internal_channels,
                    internal_channels,
                    kernel_size=kernel_size,
                    stride=1,
                    padding=padding,
                    dilation=dilation,
                    bias=bias), nn.BatchNorm2d(internal_channels), activation())

        # 1x1升维回原始通道数
        self.ext_conv3 = nn.Sequential(
            nn.Conv2d(
                internal_channels,
                channels,
                kernel_size=1,
                stride=1,
                bias=bias), nn.BatchNorm2d(channels), activation())

        self.ext_regul = nn.Dropout2d(p=dropout_prob)

        # 在添加分支之后应用的 PReLU 层
        self.out_activation = activation()

    def forward(self, x):
        # Main branch shortcut
        main = x

        # 扩展分支
        ext = self.ext_conv1(x)
        ext = self.ext_conv2(ext)
        ext = self.ext_conv3(ext)
        ext = self.ext_regul(ext)

        # ------------------------------------------实验1-02：RegularBottleneck的残差连接------------------------------------------
        #  提示：将主分支和扩展分支相加
        out = main + ext                #在此填空

        return self.out_activation(out)

# ========== 核心部分2：下采样瓶颈（降低分辨率） ==========
class DownsamplingBottleneck(nn.Module):
    """下采样瓶颈：主分支 = 最大池化(stride=2) + 零填充通道；扩展分支 = 2x2卷积(stride=2) -> 3x3卷积 -> 1x1升维
       输出 = 主分支 + 扩展分支，同时返回池化索引供上采样使用"""

    def __init__(self,
                 in_channels,
                 out_channels,
                 internal_ratio=4,
                 return_indices=False,
                 dropout_prob=0,
                 bias=False,
                 relu=True):
        super().__init__()

        # 存储后续需要用到的参数
        self.return_indices = return_indices

        # 检查内部“scale”参数是否在预期范围内
        # [1， 通道数]
        if internal_ratio <= 1 or internal_ratio > in_channels:
            raise RuntimeError("Value out of range. Expected value in the "
                               "interval [1, {0}], got internal_scale={1}. "
                               .format(in_channels, internal_ratio))

        internal_channels = in_channels // internal_ratio

        if relu:
            activation = nn.ReLU
        else:
            activation = nn.PReLU

        # 主分支 - 先进行最大池化操作，然后对特征图（通道）进行填充操作
        self.main_max1 = nn.MaxPool2d(
            2,
            stride=2,
            return_indices=return_indices)

        # 扩展分支 - 先进行 2x2 卷积，然后是常规、扩张或不对称卷积，最后再进行一次 1x1 卷积。数字通道数量翻倍了。
        # 2x2 块的步长为 2 的投影卷积
        self.ext_conv1 = nn.Sequential(
            nn.Conv2d(
                in_channels,
                internal_channels,
                kernel_size=2,
                stride=2,
                bias=bias), nn.BatchNorm2d(internal_channels), activation())

        # 卷积
        self.ext_conv2 = nn.Sequential(
            nn.Conv2d(
                internal_channels,
                internal_channels,
                kernel_size=3,
                stride=1,
                padding=1,
                bias=bias), nn.BatchNorm2d(internal_channels), activation())

        # 1×1 扩展卷积
        self.ext_conv3 = nn.Sequential(
            nn.Conv2d(
                internal_channels,
                out_channels,
                kernel_size=1,
                stride=1,
                bias=bias), nn.BatchNorm2d(out_channels), activation())

        self.ext_regul = nn.Dropout2d(p=dropout_prob)

        # 在将分支连接起来之后应用的 PReLU 层
        self.out_activation = activation()

    def forward(self, x):
        # Main branch shortcut
        if self.return_indices:
            main, max_indices = self.main_max1(x)
        else:
            main = self.main_max1(x)

        # 扩展分支
        ext = self.ext_conv1(x)
        ext = self.ext_conv2(ext)
        ext = self.ext_conv3(ext)
        ext = self.ext_regul(ext)

        #------------------------------------------实验1-03：DownsamplingBottleneck的通道填充------------------------------------------
        # 主分支通道填充
        n, ch_ext, h, w = ext.size()
        ch_main = main.size()[1]
        #请补全代码，创建正确形状的填充张量。
        #提示：创建形状为(n, ch_ext - ch_main, h, w)的全零张量
        padding = padding = torch.zeros(n, ch_ext - ch_main, h, w)                #在此填空

        # 在进行连接操作之前，先检查主数据是在 CPU 还是 GPU 上，并据此进行相应的填充转换操作
        if main.is_cuda:
            padding = padding.cuda()

        # 合并
        main = torch.cat((main, padding), 1)

        # 添加主分支和扩展分支
        out = main + ext

        return self.out_activation(out), max_indices

# ========== 核心部分3：上采样瓶颈（恢复分辨率） ==========
class UpsamplingBottleneck(nn.Module):
    """上采样瓶颈：主分支 = 1x1卷积 -> 最大反池化(用保存的索引)；扩展分支 = 1x1降维 -> 转置卷积(上采样) -> 1x1升维
       输出 = 主分支 + 扩展分支
    """

    def __init__(self,
                 in_channels,
                 out_channels,
                 internal_ratio=4,
                 dropout_prob=0,
                 bias=False,
                 relu=True):
        super().__init__()

        # Check in the internal_scale parameter is within the expected range
        # [1, channels]
        if internal_ratio <= 1 or internal_ratio > in_channels:
            raise RuntimeError("Value out of range. Expected value in the "
                               "interval [1, {0}], got internal_scale={1}. "
                               .format(in_channels, internal_ratio))

        internal_channels = in_channels // internal_ratio

        if relu:
            activation = nn.ReLU
        else:
            activation = nn.PReLU

        # 主分支 - 先进行最大池化操作，然后对特征图（通道）进行填充操作
        self.main_conv1 = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=1, bias=bias),
            nn.BatchNorm2d(out_channels))

        # 要记住，步长与卷积核大小相同，这一点与最大池化层的情况一样。
        self.main_unpool1 = nn.MaxUnpool2d(kernel_size=2)

        # 扩展分支 - 先进行 1x1 卷积，然后是常规、扩张或不对称卷积，最后再进行一次 1x1 卷积。数字通道数量翻倍了。
        # 1×1 剖面卷积（步长为 1）
        self.ext_conv1 = nn.Sequential(
            nn.Conv2d(
                in_channels, internal_channels, kernel_size=1, bias=bias),
            nn.BatchNorm2d(internal_channels), activation())

        # Transposed convolution
        self.ext_tconv1 = nn.ConvTranspose2d(
            internal_channels,
            internal_channels,
            kernel_size=2,
            stride=2,
            bias=bias)
        self.ext_tconv1_bnorm = nn.BatchNorm2d(internal_channels)
        self.ext_tconv1_activation = activation()

        # 1×1 扩展卷积
        self.ext_conv2 = nn.Sequential(
            nn.Conv2d(
                internal_channels, out_channels, kernel_size=1, bias=bias),
            nn.BatchNorm2d(out_channels))

        self.ext_regul = nn.Dropout2d(p=dropout_prob)

        # 在将分支连接起来之后应用的 PReLU 层
        self.out_activation = activation()

    def forward(self, x, max_indices, output_size):
        # Main branch shortcut
        main = self.main_conv1(x)
        main = self.main_unpool1(
            main, max_indices, output_size=output_size)

        # Extension branch
        ext = self.ext_conv1(x)
        ext = self.ext_tconv1(ext, output_size=output_size)
        ext = self.ext_tconv1_bnorm(ext)
        ext = self.ext_tconv1_activation(ext)
        ext = self.ext_conv2(ext)
        ext = self.ext_regul(ext)

        # Add main and extension branches
        out = main + ext

        return self.out_activation(out)

# ========== 完整ENet模型 ==========
class ENet(nn.Module):
    """ENet整体架构：5个Stage（3个编码器 + 2个解码器）"""

    def __init__(self, num_classes, encoder_relu=False, decoder_relu=True):
        super().__init__()
        # Stage 0: 初始下采样
        self.initial_block = InitialBlock(3, 16, relu=encoder_relu)

        # Stage 1: 编码器 (下采样 + 4个Regular)
        self.downsample1_0 = DownsamplingBottleneck(
            16,
            64,
            return_indices=True,
            dropout_prob=0.01,
            relu=encoder_relu)
        self.regular1_1 = RegularBottleneck(
            64, padding=1, dropout_prob=0.01, relu=encoder_relu)
        self.regular1_2 = RegularBottleneck(
            64, padding=1, dropout_prob=0.01, relu=encoder_relu)
        self.regular1_3 = RegularBottleneck(
            64, padding=1, dropout_prob=0.01, relu=encoder_relu)
        self.regular1_4 = RegularBottleneck(
            64, padding=1, dropout_prob=0.01, relu=encoder_relu)

        # Stage 2: 编码器 (下采样 + 多种空洞/非对称卷积)
        self.downsample2_0 = DownsamplingBottleneck(
            64,
            128,
            return_indices=True,
            dropout_prob=0.1,
            relu=encoder_relu)
        self.regular2_1 = RegularBottleneck(
            128, padding=1, dropout_prob=0.1, relu=encoder_relu)
        self.dilated2_2 = RegularBottleneck(
            128, dilation=2, padding=2, dropout_prob=0.1, relu=encoder_relu)
        self.asymmetric2_3 = RegularBottleneck(
            128,
            kernel_size=5,
            padding=2,
            asymmetric=True,
            dropout_prob=0.1,
            relu=encoder_relu)
        self.dilated2_4 = RegularBottleneck(
            128, dilation=4, padding=4, dropout_prob=0.1, relu=encoder_relu)
        self.regular2_5 = RegularBottleneck(
            128, padding=1, dropout_prob=0.1, relu=encoder_relu)
        self.dilated2_6 = RegularBottleneck(
            128, dilation=8, padding=8, dropout_prob=0.1, relu=encoder_relu)
        self.asymmetric2_7 = RegularBottleneck(
            128,
            kernel_size=5,
            asymmetric=True,
            padding=2,
            dropout_prob=0.1,
            relu=encoder_relu)
        self.dilated2_8 = RegularBottleneck(
            128, dilation=16, padding=16, dropout_prob=0.1, relu=encoder_relu)

        # Stage 3: 编码器 (不改变分辨率，继续提取特征)
        self.regular3_0 = RegularBottleneck(
            128, padding=1, dropout_prob=0.1, relu=encoder_relu)
        self.dilated3_1 = RegularBottleneck(
            128, dilation=2, padding=2, dropout_prob=0.1, relu=encoder_relu)
        self.asymmetric3_2 = RegularBottleneck(
            128,
            kernel_size=5,
            padding=2,
            asymmetric=True,
            dropout_prob=0.1,
            relu=encoder_relu)
        self.dilated3_3 = RegularBottleneck(
            128, dilation=4, padding=4, dropout_prob=0.1, relu=encoder_relu)
        self.regular3_4 = RegularBottleneck(
            128, padding=1, dropout_prob=0.1, relu=encoder_relu)
        self.dilated3_5 = RegularBottleneck(
            128, dilation=8, padding=8, dropout_prob=0.1, relu=encoder_relu)
        self.asymmetric3_6 = RegularBottleneck(
            128,
            kernel_size=5,
            asymmetric=True,
            padding=2,
            dropout_prob=0.1,
            relu=encoder_relu)
        self.dilated3_7 = RegularBottleneck(
            128, dilation=16, padding=16, dropout_prob=0.1, relu=encoder_relu)

        # Stage 4: 解码器 (上采样 + 2个Regular)
        self.upsample4_0 = UpsamplingBottleneck(
            128, 64, dropout_prob=0.1, relu=decoder_relu)
        self.regular4_1 = RegularBottleneck(
            64, padding=1, dropout_prob=0.1, relu=decoder_relu)
        self.regular4_2 = RegularBottleneck(
            64, padding=1, dropout_prob=0.1, relu=decoder_relu)

        # Stage 5: 解码器 (上采样 + 1个Regular + 最终转置卷积)
        self.upsample5_0 = UpsamplingBottleneck(
            64, 16, dropout_prob=0.1, relu=decoder_relu)
        self.regular5_1 = RegularBottleneck(
            16, padding=1, dropout_prob=0.1, relu=decoder_relu)
        self.transposed_conv = nn.ConvTranspose2d(
            16,
            num_classes,
            kernel_size=3,
            stride=2,
            padding=1,
            bias=False)

    def forward(self, x):
        # Initial block
        input_size = x.size()
        x = self.initial_block(x)

        # 编码器 Stage1
        stage1_input_size = x.size()
        x, max_indices1_0 = self.downsample1_0(x)
        x = self.regular1_1(x)
        x = self.regular1_2(x)
        x = self.regular1_3(x)
        x = self.regular1_4(x)

        # 编码器 Stage2
        stage2_input_size = x.size()
        x, max_indices2_0 = self.downsample2_0(x)
        x = self.regular2_1(x)

        #------------------------------------------实验1-04：Encoder中Dilated Bottleneck的选择------------------------------------------
        # 请从以下选项中选出正确的一项：
        # A.self.regular2_1
        # B.self.dilated2_2
        # C.self.asymmetric2_3
        # D.self.dilated2_4
        x =  self.dilated2_2(x)                                     #在此填空

        x = self.asymmetric2_3(x)
        x = self.dilated2_4(x)
        x = self.regular2_5(x)
        x = self.dilated2_6(x)
        x = self.asymmetric2_7(x)
        x = self.dilated2_8(x)

        # 编码器 Stage3 (分辨率保持 H/8,W/8)
        x = self.regular3_0(x)
        x = self.dilated3_1(x)
        x = self.asymmetric3_2(x)
        x = self.dilated3_3(x)
        x = self.regular3_4(x)
        x = self.dilated3_5(x)
        x = self.asymmetric3_6(x)
        x = self.dilated3_7(x)

        # 解码器 Stage4
        x = self.upsample4_0(x, max_indices2_0, output_size=stage2_input_size)
        x = self.regular4_1(x)
        x = self.regular4_2(x)

        # 解码器 Stage5
        x = self.upsample5_0(x, max_indices1_0, output_size=stage1_input_size)
        x = self.regular5_1(x)

        #------------------------------------------实验1-05：ENet的最终输出层------------------------------------------
        #请补全代码，完成最终的输出。
        # 提示：用self.transposed_conv上采样回原始尺寸，指定output_size=input_size
        x = self.transposed_conv(x, output_size=input_size)                                            #在此填空

        return x
