//
// Created by caffe on 19-7-16.
//

#include "../../include/tps/Tps.h"
using namespace tps;
using namespace std;
Tps::Tps() {
    map<string,string> confMap;
    readConf(confFilePath,confMap);
    map<string,string>::iterator iter;

    /**read configure file and initial private value**/
    iter = confMap.find("CameraImagesRoot");
    camImRoot = iter->second;
    iter = confMap.find("ProjectImagesRoot");
    prjImRoot = iter->second;
}

void Tps::loadImgs() {
    /**
     * brief : loads all images in the 'camImRoot' and 'prjImRoot' to vector<Mat>
     */
    /**reads all image's name to a vector**/
    vector<cv::String> camImPath;
    vector<cv::String> prjImPath;
    cv::glob(camImRoot,camImPath);
    cv::glob(prjImRoot,prjImPath);
    /**travels all image in the directory and read them to the vector**/
    for (auto path:camImPath){
        cv::Mat img = cv::imread(path,CV_LOAD_IMAGE_UNCHANGED);
        cv::Mat imf;
        img.convertTo(imf,CV_32FC3,1/255.);
        camImList.push_back(imf);
        img.release();
        imf.release();
    }
    for (auto path:prjImPath){
        cv::Mat img = cv::imread(path,CV_LOAD_IMAGE_UNCHANGED);
        cv::Mat imf;
        img.convertTo(imf,CV_32FC3,1/255.);
        prjImList.push_back(imf);
        img.release();
        imf.release();
    }
    /**initial N**/
    N = camImList.size();
    /**check the list size**/
    if(camImList.size()!=prjImList.size()){
        perror("error raise in loadImgs(),the number of camcapIm is not equal to prjIm");
    }
}

Eigen::MatrixXf Tps::loadQ(const int rows, const int cols){
    /**
     * brief : load the matrix of Q=[q1,q2,...,qn] of indentified rows and cols
     *
     * rows : the rows
     *
     * cols : the cols
     *
     * return null;
     */
     Eigen::MatrixXf Q(N,4);
     for(size_t i=0;i<N;i++){
         cv::Mat camIm = camImList[i];
         float_t b = camIm.ptr<cv::Vec3f>(rows)[cols][0];//b
         float_t g = camIm.ptr<cv::Vec3f>(rows)[cols][1];//g
         float_t r = camIm.ptr<cv::Vec3f>(rows)[cols][2];//r
         Q(i,0) = 1.;
         Q(i,1) = b;
         Q(i,2) = g;
         Q(i,3) = r;
     }
    return Q;
}

Eigen::MatrixXf Tps::loadP(const int rows, const int cols) {
    /**
    * brief : load the matrix of P=[p1,p2,...,pn] of indentified rows and cols
    *
    * rows : the rows
    *
    * cols : the cols
    *
    * return null;
    */
    Eigen::MatrixXf P(N,3);
    for(size_t i=0;i<N;i++){
        cv::Mat prjIm = prjImList[i];
        float_t b = prjIm.ptr<cv::Vec3f>(rows)[cols][0];//b
        float_t g = prjIm.ptr<cv::Vec3f>(rows)[cols][1];//g
        float_t r = prjIm.ptr<cv::Vec3f>(rows)[cols][2];//r
        P(i,0) = b;
        P(i,1) = g;
        P(i,2) = r;
    }
    return P;
}

Eigen::MatrixXf Tps::loadK(Eigen::MatrixXf& Q) {
    /**
     * brief :computes the matrix of K
     *
     * Q : the matirx of Q=[q1,q2,...,qn]
     *
     * return K: a NXN matrix
     */
     Eigen::MatrixXf K(N,N);
     for(size_t i=0;i<N;i++){
         for(size_t j=0;j<N;j++){
             double_t Kij=0.;
             for(size_t k=0;k<4;k++){
                 Kij += pow(Q(i,k) - Q(j,k),2);
             }
             Kij = fi(sqrt(Kij));
             K(i,j)=Kij;
         }
     }
    return K;
}


Eigen::MatrixXf Tps::loadL(Eigen::MatrixXf& Q,Eigen::MatrixXf& K) {
    /**
     * brief : combine Q and K into matrix L
     *
     * rows : the rows
     *
     * cols : the cols
     *
     * return L: matrix of (N+4)X(N+4)
     */
     Eigen::MatrixXf L(N+4,N+4);
     Eigen::MatrixXf Qt = Q.transpose();
     Eigen::MatrixXf O = Eigen::ArrayXXf::Zero(4,4);
     L.topLeftCorner(N,N)=K;
     L.topRightCorner(4,N)=Q;
     L.bottomLeftCorner(N,4)=Qt;
     L.bottomRightCorner(4,4)=O;
    return L;
}

Eigen::MatrixXf Tps::computeW(Eigen::MatrixXf &L, Eigen::MatrixXf &P) {
    /**
     * brief : computes the weight matrix of w
     *
     * L : the L matrix of (N+4)x(Nx4)
     *
     * P : the P matrix of Nx3
     *
     * return W : the weight matrix of (N+4)x4
     */
     Eigen::MatrixXf Linv = L.inverse();
     Eigen::MatrixXf b(N+4,3);
     Eigen::MatrixXf W(N+4,3);
     b.topLeftCorner(N,4)=P;
     b.bottomLeftCorner(4,3) = Eigen::ArrayXXf::Zero(4,3);
     W=Linv*b;
    return W;
}

double Tps::fi(double d){
    if(d==0){
        return 0.;
    } else{
        return pow(d,2)*log(d);
    }
}