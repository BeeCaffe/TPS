//
// Created by caffe on 19-7-16.
//

#ifndef TPS_TPS_H
#define TPS_TPS_H
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "../../include/utils/utils.h"
namespace tps {
    class Tps {
    public:
        Tps();
        ~Tps()= default;
        /**getter and setter**/
        int getRows(){ return rows;}
        int getCols(){ return cols;}
        vector<cv::Mat> getCamImList(){ return camImList;}
        vector<cv::Mat> getPrjImList(){ return prjImList;}

        /**
         * load all images in 'camera capture images' file dir and 'projection images' file dir's images to
         * vector 'camImList' and 'prjImList',and then load Q and P matrix of Q=[q1,q2,...,qn],P=[p1,p2,...,pn]
         * */
        void loadImgs();
        Eigen::MatrixXf loadP(const int rows,const int cols);
        Eigen::MatrixXf loadQ(const int rows,const int cols);
        Eigen::MatrixXf loadK(Eigen::MatrixXf& Q);
        Eigen::MatrixXf loadL(Eigen::MatrixXf& Q, Eigen::MatrixXf& K);
        Eigen::MatrixXf computeW(Eigen::MatrixXf& L,Eigen::MatrixXf& P);

        /**other functions**/
        double fi(double d);
    private:
        const int rows = 768;
        const int cols = 1024;
        std::vector<cv::Mat> camImList;
        std::vector<cv::Mat> prjImList;
        std::string camImRoot;
        std::string prjImRoot;
        const std::string confFilePath = "config/conf.txt";
        int N;
    };
}


#endif //TPS_TPS_H
