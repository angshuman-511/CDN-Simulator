#ifndef ORIGIN_SERVER_H
#define ORIGIN_SERVER_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class OriginServer
{
private:
    unordered_map<string, string> files;

public:
    void addFile(string name, string content);
    bool hasFile(string name);
    string getFile(string name);
    int getFileCount();
    void printFiles();
};

#endif