#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Router
{
private:
    unordered_map<string, int> cityToEdge;

public:
    Router();

    void addRoute(string city, int edgeId);

    int getNearestEdge(string city);

    bool hasRoute(string city);

    void printRoutes();
};

#endif
