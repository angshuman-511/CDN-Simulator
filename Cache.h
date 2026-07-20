#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class Cache
{
private:
    int capacity;
    list<string> accessOrder;
    unordered_map<string, string> files;
    unordered_map<string, list<string>::iterator> iteratorMap;

    void evict();

public:
    Cache(int size = 5);

    bool contains(string file);

    string get(string file);

    void put(string file, string content);

    void clear();

    int getSize();

    int getCapacity();

    void printContents();
};

#endif
