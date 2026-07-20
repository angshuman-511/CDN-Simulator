#include "Router.h"

Router::Router()
{
}

void Router::addRoute(string city, int edgeId)
{
    cityToEdge[city] = edgeId;
}

int Router::getNearestEdge(string city)
{
    if (cityToEdge.find(city) != cityToEdge.end())
    {
        return cityToEdge[city];
    }
    return -1; // No route found
}

bool Router::hasRoute(string city)
{
    return cityToEdge.find(city) != cityToEdge.end();
}

void Router::printRoutes()
{
    cout << "  Routing Table:" << endl;
    if (cityToEdge.empty())
    {
        cout << "    (no routes configured)" << endl;
        return;
    }
    for (auto& pair : cityToEdge)
    {
        cout << "    " << pair.first << " --> Edge Server " << pair.second << endl;
    }
}