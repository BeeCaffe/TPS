#include "../include/utils/utils.h"
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
int main(){
//    readConfTest();
//    savetxtTest();
    loadtxtTest();
    return 0;
}