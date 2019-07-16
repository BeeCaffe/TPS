#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main() {
    std::cout << "Hello, World!" << std::endl;
    cv::Mat img = imread("1.jpg");
    imshow("img",img);
    cv::waitKey(0);
    return 0;
}