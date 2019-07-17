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