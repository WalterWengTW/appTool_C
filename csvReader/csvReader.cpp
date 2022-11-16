#include "csvReader.h"

bool csvReader::csvRead(std::string name)
{
    CSVFileName = name;
    std::fstream file;
    file.open(CSVFileName, std::ios::in);
    if(!file.is_open())
        return false;
    cfg.clear();
    std::string line;
    while(std::getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if( std::getline(is_line, key, ',') )
        {
            std::string value;
            std::vector<std::string> values;
            while(std::getline(is_line, value, ','))
            {
                values.push_back(value);
            }
            if( std::getline(is_line, value))
                values.push_back(value);
            cfg.insert(std::pair<std::string, std::vector<std::string>>(key, values));
        }
    }
    file.close();
    return true;
}

bool csvReader::csvCreate(std::string name)
{
    std::fstream file;
    file.open(name, std::ios::in);
    if(!file.is_open())
    {
        cfg.clear();
        CSVFileName = name;
        file.open(CSVFileName, std::ios::out | std::ios::trunc);
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

bool csvReader::csvSave()
{
    if(CSVFileName == "") return false;
    std::fstream file;
    file.open(CSVFileName, std::ios::out | std::ios::trunc);
    std::map<std::string, std::vector<std::string>>::iterator it;

    for(it = cfg.begin(); it != cfg.end(); it++)
    {
        if(it->first.c_str()[0] == '#')
        {
            file << it->first;
            for(int i = 0; i < it->second.size(); ++i)
                file << "," << it->second[i];
            file << "\n";
        }
    }

    for(it = cfg.begin(); it != cfg.end(); it++)
    {
        if(it->first.c_str()[0] != '#')
        {
            file << it->first;
            for(int i = 0; i < it->second.size(); ++i)
                file << "," << it->second[i];
            file << "\n";
        }
    }
    file.close();
    return true;
}





int csvReader::getKeyCount(std::string key)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
        it = cfg.find(key);
    if(it != cfg.end())
        return it->second.size();
    return -1;
}

bool csvReader::isKeyExists(std::string key)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
        return true;
    return false;
}


template<>
int csvReader::get<int>(std::string key, int index)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        if(index >= it->second.size())
            return -INT_MAX;
        else
            return atoi(it->second[index].c_str());
    }
    return -INT_MAX;
}

template<>
double csvReader::get<double>(std::string key, int index)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        if(index >= it->second.size())
            return -1e-16;
        else
            return std::stof(it->second[index].c_str());
    }
    return -1e-16;
}

template<>
std::string csvReader::get<std::string>(std::string key, int index)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        if(index >= it->second.size())
            return std::string("");
        else
            return it->second[index];
    }
    return std::string("");
}


bool csvReader::add(std::string key, std::vector<int> value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it == cfg.end())
    {
        std::vector<std::string> values;
        for(int i = 0; i < value.size(); ++i)
            values.push_back(std::to_string(value[i]));
        cfg.insert(std::pair<std::string, std::vector<std::string>>(key, values));
        csvSave();
        return true;
    }
    return false;
}


bool csvReader::add(std::string key, std::vector<double> value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it == cfg.end())
    {
        std::vector<std::string> values;
        for(int i = 0; i < value.size(); ++i)
            values.push_back(std::to_string(value[i]));
        cfg.insert(std::pair<std::string, std::vector<std::string>>(key, values));
        csvSave();
        return true;
    }
    return false;
}

bool csvReader::add(std::string key, std::vector<std::string> value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it == cfg.end())
    {
        cfg.insert(std::pair<std::string, std::vector<std::string>>(key, value));
        csvSave();
        return true;
    }
    return false;
}


void csvReader::rm(std::string key)
{
    cfg.erase(key);
    csvSave();
}


bool csvReader::md(std::string key, int index, int value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        if(index>=it->second.size())
            return false;
        else
        {
            it->second[index] = std::to_string(value);
            csvSave();
            return true;
        }
    }
    return false;
}



bool csvReader::md(std::string key, int index, double value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        if(index>=it->second.size())
            return false;
        else
        {
            it->second[index] = std::to_string(value);
            csvSave();
            return true;
        }
    }
    return false;

}


bool csvReader::md(std::string key, int index, std::string value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        if(index>=it->second.size())
            return false;
        else
        {
            it->second[index] = value;
            csvSave();
            return true;
        }
    }
    return false;
}


bool csvReader::replace(std::string key, std::vector<std::string> value)
{
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = cfg.find(key);
    if(it != cfg.end())
    {
        it->second.clear();
        it->second.assign(value.begin(), value.end());
        csvSave();
        return true;
    }
    return false;
}















