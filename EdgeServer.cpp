#include "EdgeServer.h"

EdgeServer::EdgeServer(int id, string region, int cacheCapacity)
    : id(id), region(region), cache(cacheCapacity)
{
}

bool EdgeServer::hasFile(string filename)
{
    return cache.contains(filename);
}

string EdgeServer::getFile(string filename)
{
    return cache.get(filename);
}

void EdgeServer::storeFile(string filename, string content)
{
    cache.put(filename, content);
}

int EdgeServer::getID()
{
    return id;
}

string EdgeServer::getRegion()
{
    return region;
}

void EdgeServer::clearCache()
{
    cache.clear();
    cout << "  [Edge " << id << " - " << region << "] Cache cleared." << endl;
}

void EdgeServer::printCache()
{
    cout << "  Edge Server " << id << " (" << region << ") - Cache:" << endl;
    cache.printContents();
}