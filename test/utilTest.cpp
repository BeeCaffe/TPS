#include "../include/utils/utils.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
void readConfTest(){
    string confPath = "/home/caffe/CLionProjects/TPS/config/conf.txt";
    map<string,string> m_comMap;
    readConf(confPath,m_comMap);
    map<string,string>::iterator iter;
    iter = m_comMap.begin();
    while (iter!=m_comMap.end()){
        std::cout<<"key :"<<iter->first<<endl;
        std::cout<<"value :"<<iter->second<<endl;
        iter++;
    }
    map<string,string>::iterator iterMap;
    iterMap = m_comMap.find("CameraImagesRoot");
    string path = iterMap->second;
    std::cout<<path<<endl;
}

void savetxtTest(){
    tps::Tps tps1 = tps::Tps();
    tps1.loadImgs();
    Eigen::MatrixXf Q=tps1.loadQ(0,0);
    Eigen::MatrixXf K=tps1.loadK(Q);
    Eigen::MatrixXf L=tps1.loadL(Q,K);
    Eigen::MatrixXf P=tps1.loadP(0,0);
    Eigen::MatrixXf W=tps1.computeW(L,P);
    string path = "resource/weight/1.txt";
    savetxt(path,W);
}

void loadtxtTest(){
    string path = "resource/weight/1.txt";
    Eigen::MatrixXf mat = loadtxt(path);
    std::cout<<mat<<endl;
}

void midianFilterTest(){
    string imPath = "resource/compened";
    vector<cv::String> nameList;
    cv::glob(imPath,nameList);
    for (auto path:nameList){
        cv::Mat img = cv::imread(path);
//        cv::medianBlur(img,img,5);
        cout<<img<<endl;
        cv::imshow("img",img);
        cv::waitKey(0);
        cv::destroyAllWindows();
        img.release();
    }
}
int main(){
//    readConfTest();
//    savetxtTest();
//    loadtxtTest();
    midianFilterTest();
    return 0;
}