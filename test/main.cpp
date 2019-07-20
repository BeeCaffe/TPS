#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/tps/Tps.h"
using namespace cv;
using namespace tps;
void ComputeAllWeight(){
    Tps tps1 =  Tps();
    tps1.computeAllW(0);
}
void compensateImgs(){
    Tps tps1 = Tps();
    tps1.loadImgs();
    tps1.compenIms();
}
int main() {
//    ComputeAllWeight();
    compensateImgs();
}