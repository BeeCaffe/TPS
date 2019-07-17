//
// Created by caffe on 19-7-16.
//

#ifndef TPS_TPS_H
#define TPS_TPS_H
#include <opencv2/opencv.hpp>
#include <fstream>
#include <vector>
#include <map>
namespace tps {
    class Tps {
    public:
        Tps();
        ~Tps();

        /**load all images in 'camera capture images' file dir and 'projection images' file dir's images to
         *vector 'camImList' and 'prjImList'
         *
         * */
        void loadImgs();
    private:
        const int rows = 768;
        const int cols = 1024;
        std::vector<cv::Mat> camImList;
        std::vector<cv::Mat> prjImList;
        const std::string camImRoot;
        const std::string prjImRoot;
        const std::string confFilePath = "config/conf.txt";
    };
}


#endif //TPS_TPS_H
