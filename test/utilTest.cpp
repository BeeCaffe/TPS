// Created by caffe on 19-7-16.
#include "../include/utils/utils.h"
#include <iostream>
using namespace std;
void readConfTest(){
    string confPath = "/home/caffe/CLionProjects/TPS/config/conf.txt";
    map<string,string> m_comMap;
    readConf(confPath,m_comMap);
//    map<string,string>::iterator iter;
//    iter = m_comMap.begin();
//    while (iter!=m_comMap.end()){
//        std::cout<<"key :"<<iter->first<<endl;
//        std::cout<<"value :"<<iter->second<<endl;
//        iter++;
//    }
    map<string,string>::iterator iterMap;
    iterMap = m_comMap.find("CameraImagesRoot");
    string path = iterMap->second;
    std::cout<<path<<endl;
}

int main(){
    readConfTest();
    return 0;
}