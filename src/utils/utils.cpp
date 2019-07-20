//
// Created by caffe on 19-7-16.
//
#include "../../include/utils/utils.h"
using namespace std;

void readConf(string confPath, map<string,string> &m_mapConfInfo){
    /**
     * readConf(string confPath, map<string,string> &m_mapConfInfo) -> null
     *
     * brief : read the configure information in the *.conf file
     *
     * confPath : the path to *conf file.
     *
     * m_mapConfInfo : a map which is used to save the 'key' and 'value' information in configure file.
     *
     * return : nothing
     */
    ifstream configFile;

    configFile.open(confPath);

    string strLine;

    if(configFile.is_open()){

        while (!configFile.eof()) {

            getline(configFile, strLine);

            if (strLine.find('#') == 0) {
                continue;
            }

            size_t pos = strLine.find('=');

            string key = strLine.substr(0, pos);

            string value = strLine.substr(pos+1);

            m_mapConfInfo.insert(pair<string,string>(key,value));
        }
    } else{
        perror("file not exist!");
    }
}

Eigen::MatrixXf loadtxt(string& path){
    /**
     * brief : loads *.txt to Eigen matrix
     *
     * path : the *.txt file path
     *
     * return : the matrix
     */
    ifstream is;
    is.open(path,ios::in);
    string strLine;
    istringstream istr;
    vector<double > tmpVec;
    vector<vector<double>> mat;
    double tmp;
    if(is.is_open()){
        while (getline(is, strLine)) {
            istr.str(strLine);
            while (istr>>tmp){
                tmpVec.push_back(tmp);
            }
            mat.push_back(tmpVec);
            tmpVec.clear();
            istr.clear();
            strLine.clear();
        }
        is.close();
    }else{
        perror("loadtxt error : file not exist!");
    }
    size_t rows = mat.size();
    size_t cols = mat[0].size();
//    if(rows==0 || cols ==0 ){
//        perror("load txt error : *txt file is empty!");
//    }
    Eigen::MatrixXf e_mat(rows,cols);
    for(size_t i=0;i<rows;i++){
        for(size_t j=0;j<cols;j++){
            e_mat(i,j)=mat[i][j];
        }
    }
    return e_mat;
}
int savetxt(string& path,Eigen::MatrixXf mat){
    /**
     * brief : save the Eigen matrix to *.txt file
     *
     * path : the save file path.
     *
     * mat : the saved matrix
     *
     * return 0 -> ok
     *        -1 ->error
     */
     /**build the file**/
     string dir = path.substr(0,path.find_last_of('/'));
     string name = path.substr(path.find_last_of('/'),path.length());
     if (0!=access(dir.c_str(),0)){
         mkdir(path.c_str(),0775);
     }
     if(name.substr(name.find_last_of('.'),name.length())!=".txt"){
         perror("savetxt error : file format are not correct!");
         return -1;
     }
     ofstream os;
     os.open(dir+name,ios::out);
     if(os.is_open()){
         os<<mat;
     } else{
         perror("savetxt error : file not exist!");
         return -1;
     }
     os.close();
    return 0;
}

void process(const int now, const int total , time_t statTm, time_t endTm){
    /**
     * brief : this function is used to show the process of program.
     *
     * now : the number of now.
     *
     * total : the number of total.
     *
     * statTm : start time.
     *
     * endTm : end time
     */
     int range = 100;
     time_t detaTm = endTm - statTm;
     time_t h = detaTm/3600;
     time_t m = (detaTm-h*3600)/60;
     time_t s = detaTm%60;
     double pcent = ((double)now/total)*100;
     printf("Number : %d/%d | Rate : %2.4lf%% | Time : %d:%d:%d | [",now,total,pcent,h,m,s);
     for(size_t i=0;i<pcent-1;i++){
         printf("=");
     }
     printf(">");
     for(size_t j=pcent;j<range;j++ ){
         printf(" ");
     }
     printf("]\n");
}