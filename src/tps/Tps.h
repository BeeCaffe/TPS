//
// Created by caffe on 19-7-16.
//

#ifndef TPS_TPS_H
#define TPS_TPS_H
#include <opencv2/opencv.hpp>
#include <vector>
namespace tps {
    class Tps {
    public:
        Tps();
        ~Tps();
    private:
        const int rows = 768;
        const int cols = 1024;
        std::vector<cv::Mat> camImList;
        std::vector<cv::Mat> prjImList;
    };
}


#endif //TPS_TPS_H
