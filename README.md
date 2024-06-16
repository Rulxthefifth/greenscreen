# 基于OpenCV实现绿幕抠图

本代码基于openCV代码，实现绿幕抠图，并黏贴至所需背景的目的。

示例所用原图及背景如下所示
原图：
![原图](https://github.com/Rulxthefifth/greenscreen/blob/main/%E5%8E%9F%E5%9B%BE.jpg)

![背景图](https://github.com/Rulxthefifth/greenscreen/blob/main/%E8%83%8C%E6%99%AF%E5%9B%BE.jpg)

## 1. Png图像格式下的绿幕抠图
我们将原来的**jpg**格式的绿幕图像转换到有透明度空间的**png**格式，通过约束png特有的透明度的值识别绿幕的绿色点的位置，然后对该点的绿色通道值置零即可去除绿幕。

代码实现：
```c++
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace cv;
using namespace std;

int main()
{
    //1、设置需要去除的颜色
    //2、颜色比对
    //3、展示效果
    Mat srcImg = imread("C:/Users/41448/Desktop/1.jpg", -1);
    cout << srcImg.channels() << endl;

    Vec3b color(0, 255, 0); //绿色
    //int tempr = 0;
    int tempc = 0;
    //先把图片放大，做完抠图后再缩小。
    Mat temp;
    //转换图片，增加透明区域
    cvtColor(srcImg, temp, COLOR_RGB2BGRA);

    for (int i = 0; i < srcImg.rows; ++i) {
        for (int j = 0; j < srcImg.cols; ++j) {
            Vec3b& pixel = srcImg.at<Vec3b>(i, j);
            Vec4b& pixel_temp = temp.at<Vec4b>(i, j);

            //if (pixel[0] <= 30 && pixel[1] >= 210 && pixel[2] <= 30)
            if (pixel[1] >= 0 && pixel[2] <= 30)
            {
                tempc = j + 1; 
                pixel_temp[1] = 0;
                //pixel[0] = 255;
                //pixel[1] = 255;
                //pixel[2] = 255;
            }
            else if (tempc == j - 1)
            {
                pixel_temp[1] = 0;//把符合要求的下一个点也抠掉
                /*pixel[0] = 255;
                pixel[1] = 255;
                pixel[2] = 255;*/
            }
        }
    }
    imshow("result", temp);
    imwrite("D:/result.png", temp);
    waitKey(0);
    return 0;
}

```

![2.png](https://github.com/Rulxthefifth/greenscreen/blob/main/2.png)
问题：
**颜色阈值设置不当**
代码中使用了if (pixel[1] >= 0 && pixel[2] <= 40)作为判断条件，可能没有正确地覆盖所有需要被识别为绿色像素的范围，在实际操作中需要不断测试所需要的值的大小，导致某些绿幕点无法识别，有些图像内包含的绿色点被错误识别。

**边缘处理问题**
在进行颜色阈值判断时，仅考虑了当前像素不足以使得边缘处平滑过渡，分析可能是边缘像素可能因为光照、阴影或其他因素而颜色略有偏差，导致没有被正确识别，从而导致边缘处存在绿幕残留。

**于是我们尝试了用HSV空间进行抠图**
## 2.HSV绿幕空间抠图
HSV空间更适合进行绿幕抠图，于是我们转换了颜色空间，并使用inRange函数来更精确地选择绿色像素，对边缘处的绿幕识别起到了更好的效果。
```c++
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

```
抠图结果：
![3](https://github.com/Rulxthefifth/greenscreen/blob/main/3.png)
抠图结果基本满足要求
## 3. 绿幕抠图后的图像复制

对绿幕的抠图基本满足了需求，下一步是进行抠图后的图像复制。
我们使用copyTo函数将绿幕抠图中的绿色部分用背景图进行替代。

```c++
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

```
结果：
![4](https://github.com/Rulxthefifth/greenscreen/blob/main/4.png)
