#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // ��ȡ��Ļͼ��ͱ���ͼ��
    Mat srcImg = imread("C:/Users/41448/Desktop/1.jpg", IMREAD_COLOR);
    Mat bgImg = imread("C:/Users/41448/Desktop/grass.jpg", IMREAD_COLOR);
    if (srcImg.empty() || bgImg.empty()) {
        cerr << "Could not read one or both images" << endl;
        return 1;
    }

    // ������ɫͨ����HSV��Χ
    Scalar lower_green(40, 100, 100);
    Scalar upper_green(80, 255, 255);

    // ��BGRͼ��ת��ΪHSV��ɫ�ռ�
    Mat hsvImg;
    cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);

    // ����һ�����룬����ѡ����ɫ����
    Mat mask;
    inRange(hsvImg, lower_green, upper_green, mask);

    // ������Ӧ�õ�BGRAͼ���ϣ�����ѡ�е���ɫ���ص�͸����Ϊ0
    srcImg.setTo(Scalar(0, 0, 0, 0), mask);

    // ����ɫ�����ñ���ͼ���滻
    srcImg.copyTo(bgImg, srcImg);

    // ��ʾ���
    imshow("result", bgImg);

    // ������ͼ��ע��JPG��֧��͸���ȣ���������ֱ�ӱ���ϳɺ�ı���ͼ��
    imwrite("D:/result.jpg", bgImg);

    waitKey(0); // �ȴ�������Ȼ�����
    return 0;
}

