#ifndef EDGE_SERVER_H
#define EDGE_SERVER_H

#include <iostream>
#include <string>
#include "Cache.h"

using namespace std;

class EdgeServer
{
private:
    int id;
    string region;
    Cache cache;

public:
    EdgeServer(int id, string region = "Default", int cacheCapacity = 5);

    bool hasFile(string filename);

    string getFile(string filename);

    void storeFile(string filename, string content);

    int getID();

    string getRegion();

    void clearCache();

    void printCache();
};

#endif
