#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // ��ȡͼ��-1��ʾͼ����BGRA��ʽ��ȡ������͸����ͨ��
    Mat srcImg = imread("C:/Users/41448/Desktop/1.jpg", -1);
    if (srcImg.empty()) {
        cerr << "Could not read the image" << endl;
        return 1;
    }

    // ������ɫͨ����HSV��Χ��������ɫ��ֵѡ��
    Scalar lower_green(40, 100, 100); // HSV��ɫ�ռ��е�����
    Scalar upper_green(80, 255, 255); // HSV��ɫ�ռ��е�����

    // ��BGRͼ��ת��ΪHSV��ɫ�ռ�
    Mat hsvImg;
    cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);

    // ����һ�����룬����ѡ����ɫ����
    Mat mask;
    inRange(hsvImg, lower_green, upper_green, mask);

    // ������Ӧ�õ�BGRAͼ���ϣ�����ѡ�е���ɫ���ص�͸����Ϊ0
    srcImg.setTo(Scalar(0, 0, 0, 0), mask);

    // ��ʾ���
    imshow("result2", srcImg);
    imwrite("D:/result2.png", srcImg); // ������ͼ�񣬰���͸����ͨ��

    waitKey(0); // �ȴ�������Ȼ�����
    return 0;
}
