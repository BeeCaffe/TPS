#include "../include/tps/Tps.h"
#include <vector>
using namespace std;
using namespace tps;
void loadImgsTest(){
    Tps tps1 = Tps();
    tps1.loadImgs();
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

void computeWTest(){
    Tps tps1 = Tps();
    tps1.loadImgs();
    Eigen::MatrixXf Q=tps1.loadQ(0,0);
    Eigen::MatrixXf K=tps1.loadK(Q);
    Eigen::MatrixXf L=tps1.loadL(Q,K);
    Eigen::MatrixXf P=tps1.loadP(0,0);
    Eigen::MatrixXf W=tps1.computeW(L,P);
    std::cout<<W<<endl;
}

void computeAllWTest(){
    Tps tps1= Tps();
    tps1.computeAllW(0);
}

void compenSgPxTest(){
    Tps tps1= Tps();
    Eigen::Vector3f c_in;
    c_in<<1.,1.,1.;
    Eigen::Vector3f px = tps1.compenSgPx(c_in,0,0);
    cout<<px<<endl;
}

int main(){
    loadImgsTest();
//    loadPTest();
//    loadQTest();
//    loadLTest();
//    computeWTest();
//    computeAllWTest();
//    compenSgPxTest();
}