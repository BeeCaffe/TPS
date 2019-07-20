//
// Created by caffe on 19-7-16.
//

#ifndef TPS_UTILS_H
#define TPS_UTILS_H

#include <map>
#include <string>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../include/tps/Tps.h"
#include <time.h>
using namespace std;
void readConf(string confPath, map<string,string> &m_mapConfInfo);
Eigen::MatrixXf loadtxt(string& path);
int savetxt(string& path,Eigen::MatrixXf);
void process(const int now, const int total,time_t statTm,time_t endTm);
void medianFilter(cv::Mat& img);
#endif //TPS_UTILS_H
