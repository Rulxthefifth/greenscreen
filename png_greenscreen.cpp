#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace cv;
using namespace std;

int main()
{
    //1��������Ҫȥ������ɫ
    //2����ɫ�ȶ�
    //3��չʾЧ��
    Mat srcImg = imread("C:/Users/41448/Desktop/1.jpg", -1);
    cout << srcImg.channels() << endl;

    Vec3b color(0, 255, 0); //��ɫ
    //int tempr = 0;
    int tempc = 0;
    //�Ȱ�ͼƬ�Ŵ������ͼ������С��
    Mat temp;
    //ת��ͼƬ������͸������
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
                pixel_temp[1] = 0;//�ѷ���Ҫ�����һ����Ҳ�ٵ�
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
