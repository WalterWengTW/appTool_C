#pragma once
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

typedef std::vector<int> INTVEC;
typedef std::vector<double> DBLVEC;
typedef std::vector<double> STRVEC;


class csvReader
{
private:
    std::map<std::string, std::vector<std::string>> cfg;
    std::string CSVFileName = "";


public:
    csvReader() { };
    ~csvReader() { };

    bool csvRead(std::string name);
    bool csvCreate(std::string name);
    bool csvSave();

    int getKeyCount(std::string key);
    bool isKeyExists(std::string key);

    template<typename T>
    T get(std::string key, int index);

    bool add(std::string key, std::vector<int> value);
    bool add(std::string key, std::vector<double> value);
    bool add(std::string key, std::vector<std::string> value);

    void rm(std::string key);

    bool md(std::string key, int index, int value);
    bool md(std::string key, int index, double value);
    bool md(std::string key, int index, std::string value);
    bool replace(std::string key, std::vector<std::string> value);

};
