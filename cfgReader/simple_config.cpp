#include "simple_config.h"


void CFG::cfgRead(std::string configName)
{
    configFileName = configName;
    std::fstream file;
    file.open(configFileName, std::ios::in);
    std::string line;
    while(std::getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if( std::getline(is_line, key, '=') )
        {
            std::string value;
            if( std::getline(is_line, value))
                config.insert(std::pair<std::string, std::string>(key, value));
            else
                config.insert(std::pair<std::string, std::string>(key, ""));
        }
    }
    file.close();
}

void CFG::add(std::string key, int value)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it == config.end())
        config.insert(std::pair<std::string, std::string>(key, std::to_string(value)));
    cfgSave();
}

void CFG::add(std::string key, double value)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it == config.end())
        config.insert(std::pair<std::string, std::string>(key, std::to_string(value)));
    cfgSave();
}

void CFG::add(std::string key, std::string value)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it == config.end())
        config.insert(std::pair<std::string, std::string>(key, value));
    cfgSave();
}

void CFG::rm(std::string key)
{
    config.erase(key);
    cfgSave();
}




bool CFG::modify(std::string key, int value)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
    {
        it->second = std::to_string(value);
        cfgSave();
        return true;
    }
    return false;
}


bool CFG::modify(std::string key, double value)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
    {
        it->second = std::to_string(value);
        cfgSave();
        return true;
    }
    return false;
}


bool CFG::modify(std::string key, std::string value)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
    {
        it->second = value;
        cfgSave();
        return true;
    }
    return false;
}


template<>
int CFG::get<int>(std::string key)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
        return atoi(it->second.c_str());
    return -INT_MAX;
}

template<>
double CFG::get<double>(std::string key)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
        return std::stof(it->second.c_str());
    return -1e-16;
}

template<>
std::string CFG::get<std::string>(std::string key)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
        return it->second;
    return std::string("");
}


bool CFG::isKeyExists(std::string key)
{
    std::map<std::string, std::string>::iterator it;
    it = config.find(key);
    if(it != config.end())
        return true;
    return false;
}


bool CFG::cfgSave()
{
    std::fstream file;
    file.open(configFileName, std::ios::out | std::ios::trunc);
    std::map<std::string, std::string>::iterator it;

    for(it = config.begin(); it != config.end(); it++)
        file << it->first << "=" << it->second << "\n";
    file.close();
    return true;
}


