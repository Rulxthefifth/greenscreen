#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像，-1表示图像以BGRA格式读取，包含透明度通道
    Mat srcImg = imread("C:/Users/41448/Desktop/1.jpg", -1);
    if (srcImg.empty()) {
        cerr << "Could not read the image" << endl;
        return 1;
    }

    // 定义绿色通道的HSV范围，用于颜色阈值选择
    Scalar lower_green(40, 100, 100); // HSV颜色空间中的下限
    Scalar upper_green(80, 255, 255); // HSV颜色空间中的上限

    // 将BGR图像转换为HSV颜色空间
    Mat hsvImg;
    cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);

    // 创建一个掩码，用于选择绿色像素
    Mat mask;
    inRange(hsvImg, lower_green, upper_green, mask);

    // 将掩码应用到BGRA图像上，设置选中的绿色像素的透明度为0
    srcImg.setTo(Scalar(0, 0, 0, 0), mask);

    // 显示结果
    imshow("result2", srcImg);
    imwrite("D:/result2.png", srcImg); // 保存结果图像，包含透明度通道

    waitKey(0); // 等待按键，然后继续
    return 0;
}
