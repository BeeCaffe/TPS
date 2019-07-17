#include "../include/tps/Tps.h"
#include <vector>
using namespace std;
using namespace tps;
void loadImgsTest(){
    Tps tps1 = Tps();
    tps1.loadImgs();
    vector<cv::Mat> camImList = tps1.getCamImList();
    for(auto im:camImList){
     std::cout<< sizeof(im.ptr<cv::Vec3f>(0)[0][0])<<endl;
    }
}

void loadPTest(){
    Tps tps1 = Tps();
    tps1.loadImgs();
    Eigen::MatrixXf P=tps1.loadP(0,0);
    std::cout<<P<<endl;
}

void loadQTest(){
    Tps tps1 = Tps();
    tps1.loadImgs();
    Eigen::MatrixXf Q=tps1.loadQ(0,0);
    std::cout<<Q<<endl;
}

void loadLTest(){
    Tps tps1 = Tps();
    tps1.loadImgs();
    Eigen::MatrixXf Q=tps1.loadQ(0,0);
    Eigen::MatrixXf K=tps1.loadK(Q);
    Eigen::MatrixXf L=tps1.loadL(Q,K);
    std::cout<<L<<endl;
}

int main(){
//    loadImgsTest();
//    loadPTest();
//    loadQTest();
    loadLTest();
}