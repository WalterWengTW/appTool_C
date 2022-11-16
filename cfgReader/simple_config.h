/*************************************************************************************
 *
 * Simple config reader
 *
 * Auther : Walter Weng
 * Date   : 2022/03/10
 *
*************************************************************************************/


#pragma once
#include <iostream>
#include <string.h>
#include <map>
#include <fstream>
#include <sstream>

class CFG
{

private:
    std::map<std::string, std::string> config;
    std::string configFileName;

public:
    CFG(){};
    ~CFG(){};

    /*
    * Function cfgRead() read config file via file stream.This function will
    * create new file when target file is not existed.
    *
    * Arguments:
    *   configName - target reading file name. Default is "Config.cfg"
    */
    void cfgRead(std::string configName = "Config.cfg");


    /*
    * Function get() value in private member, config, that is a container
    * named map.To get corresponding type of value, it should be indicated
    * data type when using this function.
    *
    * Arguments:
    *   key - the key word you want to get paired value.
    *
    * Return:
    *   a value, and type is same as indicated.
    *
    * Example:
    *   int value = get<int>(key);
    *   double value = get<double>(key);
    *   std::string value = get<std::string>(key);
    */
    template<typename T>
    T get(std::string key);


    /*
    * Function add() can add new key and value pair into config container.
    * This object support three types of value, but key only use string
    * type. Same name of add function overloading for different type value
    * input.
    *
    * Attention:
    * This operation will save into config file when you execute it.
    *
    * Arguments:
    *   key - the key word you want to add.
    *   value - value for corresponding key word.
    */
    void add(std::string key, int value);
    void add(std::string key, double value);
    void add(std::string key, std::string value);


     /*
    * Function rm() can remove one of key and value pair in config container.
    *
    * Attention:
    * This operation will save into config file when you execute it.
    *
    * Arguments:
    *   key - the key word you want to remove.
    */
    void rm(std::string key);


    /*
    * Function modify() can edit the value corresponding key.Same name of
    * add function overloading for different type value input.
    *
    * Attention:
    * This operation will save into config file when you execute it.
    *
    * Arguments:
    *   key - the key word you want to modify.
    *   value - the value you want to change to.
    *
    * Return:
    *   boolean value means modifying success or not.
    */
    bool modify(std::string key, int value);
    bool modify(std::string key, double value);
    bool modify(std::string key, std::string value);


     /*
    * Function isKeyExists() for checking the key want to know it existing
    * or not.
    *
    * Arguments:
    *   key - the key word you want to check.
    *
    * Return:
    *   boolean value means the key existing or not.
    */
    bool isKeyExists(std::string key);

    bool cfgSave();
};

