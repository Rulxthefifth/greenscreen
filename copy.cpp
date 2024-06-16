#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取绿幕图像和背景图像
    Mat srcImg = imread("C:/Users/41448/Desktop/1.jpg", IMREAD_COLOR);
    Mat bgImg = imread("C:/Users/41448/Desktop/grass.jpg", IMREAD_COLOR);
    if (srcImg.empty() || bgImg.empty()) {
        cerr << "Could not read one or both images" << endl;
        return 1;
    }

    // 定义绿色通道的HSV范围
    Scalar lower_green(40, 100, 100);
    Scalar upper_green(80, 255, 255);

    // 将BGR图像转换为HSV颜色空间
    Mat hsvImg;
    cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);

    // 创建一个掩码，用于选择绿色像素
    Mat mask;
    inRange(hsvImg, lower_green, upper_green, mask);

    // 将掩码应用到BGRA图像上，设置选中的绿色像素的透明度为0
    srcImg.setTo(Scalar(0, 0, 0, 0), mask);

    // 将绿色部分用背景图像替换
    srcImg.copyTo(bgImg, srcImg);

    // 显示结果
    imshow("result", bgImg);

    // 保存结果图像，注意JPG不支持透明度，所以这里直接保存合成后的背景图像
    imwrite("D:/result.jpg", bgImg);

    waitKey(0); // 等待按键，然后继续
    return 0;
}

