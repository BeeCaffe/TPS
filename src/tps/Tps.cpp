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
    iter = confMap.find("WeightSaveRoot");
    weightSaveRoot = iter->second;
    /**if directory not exist, build it.**/
    if(0!=access(camImRoot.c_str(),0)){
        mkdir(camImRoot.c_str(),0775);
    }
    if(0!=access(prjImRoot.c_str(),0)){
        mkdir(prjImRoot.c_str(),0775);
    }
    if(0!=access(weightSaveRoot.c_str(),0)){
        mkdir(weightSaveRoot.c_str(),0775);
    }
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
//    for(auto name:camImPath){
//        std::cout<<name<<endl;
//    }
//    for(auto name:prjImPath) {
//        std::cout<<name<<endl;
//    }
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
     L.topRightCorner(N,4)=Q;
     L.bottomLeftCorner(4,N)=Qt;
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
     b.topLeftCorner(N,3)=P;
     b.bottomLeftCorner(4,3) = Eigen::ArrayXXf::Zero(4,3);
     W=Linv*b;
    return W;
}

void Tps::computeAllW(const int statRows){
    loadImgs();
    time_t statTm = time((time_t*)NULL);
    for(int i=statRows;i<rows;i++){
        for(int j=0;j<cols;j++){
            Eigen::MatrixXf Q=loadQ(i,j);
            Eigen::MatrixXf K=loadK(Q);
            Eigen::MatrixXf L=loadL(Q,K);
            Eigen::MatrixXf P=loadP(i,j);
            Eigen::MatrixXf W=computeW(L,P);
            string fileName = weightSaveRoot+"w_"+to_string(i)+'x'+to_string(j)+".txt";
            savetxt(fileName,W);
            time_t endTm = time((time_t*)NULL);
            process(i*cols+j,cols*rows,statTm,endTm);
        }
    }
}

Eigen::Vector3f Tps::compenSgPx(Eigen::Vector3f& c_in,const int rows, const int cols){
    /**
     * brief : using thin plate interpolation to compensate single piexl.
     *
     * c_in : the input [b,g,r] of single piexl.
     *
     * rows: the rows
     *
     * cols : the cols
     *
     * return : c_out -> the single pixel of [b,g,r]
     */
     loadImgs();
    string wFileNm = weightSaveRoot+"w_"+to_string(rows)+'x'+to_string(cols)+".txt";
    Eigen::MatrixXf W = loadtxt(wFileNm); //(N+4)x3
    Eigen::MatrixXf Q = loadQ(rows,cols); //(N+4)x4
    double r=0.,g=0.,b=0.;
    for(size_t i=0;i<N;i++){
        double sum=0.;
        for(size_t j=0;j<3;j++){
            sum+=pow(c_in(j)-Q(i,j+1),2);
        }
        sum = fi(sqrt(sum));
        b+=W(i,0)*sum;
        g+=W(i,1)*sum;
        r+=W(i,2)*sum;
    }
    b+=W(N,0)+W(N+1,0)*c_in[2]+W(N+2,0)*c_in[1]+W(N+3,0)*c_in[0];
    g+=W(N,0)+W(N+1,1)*c_in[2]+W(N+2,1)*c_in[1]+W(N+3,1)*c_in[0];
    r+=W(N,0)+W(N+1,2)*c_in[2]+W(N+2,2)*c_in[1]+W(N+3,2)*c_in[0];
    Eigen::Vector3f c_out;
    c_out<<b,g,r;
    return c_out;
}

cv::Mat Tps::compenSgIm(cv::Mat& img) {
    /**
     * brief : compensate singe image.
     *
     * img : the image.
     *
     * return image.
     */
     cv::Mat cpIm=img.clone();
    Eigen::Vector3f px;
    for(size_t i=0;i<img.rows;i++){
        for(size_t j=0;j<img.cols;j++){
            px(0) = img.ptr<cv::Vec3f>(i)[j][0],
            px(1) = img.ptr<cv::Vec3f>(i)[j][1],
            px(2) = img.ptr<cv::Vec3f>(i)[j][2];
            px = compenSgPx(px,rows,cols);
            cpIm.ptr<cv::Vec3f>(i)[j][0]=px(0);
            cpIm.ptr<cv::Vec3f>(i)[j][1]=px(1);
            cpIm.ptr<cv::Vec3f>(i)[j][2]=px(2);
        }
    }
    return cpIm;
}

double Tps::fi(double d){
    if(d==0){
        return 0.;
    } else{
        return pow(d,2)*log(d);
    }
}