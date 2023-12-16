from torchvision.models import vgg19
from torch import nn
from zipfile import ZipFile
from torch.utils.data import Dataset, DataLoader
from torchvision.utils import save_image
import torch.nn.functional as F
import torch
import cv2
import numpy
import time

class COCODataSet(Dataset):

    def __init__(self):
        super(COCODataSet, self).__init__()
        self.zip_files = ZipFile('./data/train2014_small.zip')
        self.data_set = []
        for file_name in self.zip_files.namelist():
            if file_name.endswith('.jpg'):
                self.data_set.append(file_name)

    def __len__(self):
        return len(self.data_set)

    def __getitem__(self, item):
        file_path = self.data_set[item]
        image = self.zip_files.read(file_path)
        image = numpy.asarray(bytearray(image), dtype='uint8')
        # TODO: 使用cv2.imdecode()函数从指定的内存缓存中读取数据，并把数据转换(解码)成彩色图像格式。
        image = cv2.imdecode(image, cv2.IMREAD_COLOR)
        # TODO: 使用cv2.resize()将图像缩放为512*512大小，其中所采用的插值方式为：区域插值
        image = cv2.resize(image, (512, 512), interpolation=cv2.INTER_AREA)
        # TODO: 使用cv2.cvtColor将图片从BGR格式转换成RGB格式
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # TODO: 将image从numpy形式转换为torch.float32,并将其归一化为[0,1]
        image = torch.from_numpy(image).type(torch.float32) / 255.0
        # TODO: 用permute函数将tensor从HxWxC转换为CxHxW
        image = image.permute(2, 0, 1)
        return image

class ResBlock(nn.Module):

    def __init__(self, c):
        super(ResBlock, self).__init__()
        self.layer = nn.Sequential(
            # 进行卷积，卷积核为3x3，保持通道数不变
            nn.Conv2d(c, c, kernel_size=3, stride=1, padding=1, bias=False),
            # 执行实例归一化
            nn.InstanceNorm2d(c),
            # 执行ReLU
            nn.ReLU(inplace=True),
            # 进行卷积，卷积核为3x3，保持通道数不变
            nn.Conv2d(c, c, kernel_size=3, stride=1, padding=1, bias=False),
            # 执行实例归一化
            nn.InstanceNorm2d(c)
        )
        
    def forward(self, x):
        #TODO: 返回残差运算的结果
        return x + self.layer(x)


class TransNet(nn.Module):

    def __init__(self):
        super(TransNet, self).__init__()
        self.layer = nn.Sequential(
            # 下采样层
            # 第一层卷积
            nn.Conv2d(3, 32, kernel_size=9, stride=1, padding=3, bias=False),
            # 实例归一化
            nn.InstanceNorm2d(32),
            # 创建激活函数ReLU
            nn.ReLU(inplace=True),
            # 第二层卷积
            nn.Conv2d(32, 64, kernel_size=3, stride=2, padding=1, bias=False),
            # 实例归一化
            nn.InstanceNorm2d(64),
            # 创建激活函数ReLU
            nn.ReLU(inplace=True),
            # 第三层卷积
            nn.Conv2d(64, 128, kernel_size=3, stride=2, padding=1, bias=False),
            # 实例归一化
            nn.InstanceNorm2d(128),
            # 创建激活函数ReLU
            nn.ReLU(inplace=True),

            # 残差层
            ResBlock(128),
            ResBlock(128),
            ResBlock(128),
            ResBlock(128),
            ResBlock(128),

            # 上采样层
            # 使用torch.nn.Upsample对特征图进行上采样
            nn.Upsample(scale_factor=2, mode='nearest'),
            # 执行卷积操作
            nn.Conv2d(128, 64, kernel_size=3, stride=1, padding=1, bias=False),
            # 实例归一化
            nn.InstanceNorm2d(64),
            # 执行ReLU操作
            nn.ReLU(inplace=True),

            # 使用torch.nn.Upsample对特征图进行上采样
            nn.Upsample(scale_factor=2, mode='nearest'),
            # 执行卷积操作
            nn.Conv2d(64, 32, kernel_size=3, stride=1, padding=1, bias=False),
            # 实例归一化
            nn.InstanceNorm2d(32),
            # 执行ReLU操作
            nn.ReLU(inplace=True),
            
            # 输出层
            # 执行卷积操作
            nn.Conv2d(32, 3, kernel_size=9, stride=1, padding=3),
            # sigmoid激活函数
            nn.Sigmoid()
        )

    def forward(self, x):
        return self.layer(x)
    


if __name__ == '__main__':
    # TODO: 使用cpu生成图像转换网络模型并保存在g_net中
    g_net = TransNet()
    # TODO: 从/models文件夹下加载网络参数到g_net中
    g_net.load_state_dict(torch.load("./models/fst.pth"))
    print("g_net build  PASS!\n")
    data_set = COCODataSet()
    print("load COCODataSet PASS!\n")

    batch_size = 1
    data_group = DataLoader(data_set,batch_size,True,drop_last=True)

    for i, image in enumerate(data_group):
        image_c = image.cpu()
        #print(image_c.shape)
        start = time.time()
        # TODO: 计算 g_net,得到image_g
        image_g = g_net(image)
        end = time.time()
        delta_time = end - start
        print("Inference (CPU) processing time: %s" % delta_time)
        #TODO: 利用save_image函数将tensor形式的生成图像image_g以及输入图像image_c以jpg格式左右拼接的形式保存在/out/cpu/文件夹下
        if image_c.shape != image_g.shape:
            # 调整 image_g_mlu 的尺寸以匹配 image_c
            image_g = F.interpolate(image_g, size=image_c.shape[2:], mode='bilinear', align_corners=False)
        
        save_image(torch.cat((image_c, image_g), -1), f"./out/mlu_cnnl_mfus/image_{i}.jpg")
    print("TEST RESULT PASS!\n")