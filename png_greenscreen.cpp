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
