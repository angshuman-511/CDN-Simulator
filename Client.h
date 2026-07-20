#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

using namespace std;

class Client
{
private:
    int clientId;
    string city;

public:
    Client(int id, string city);
    Client(string city);

    int getId();
    string getCity();
    string requestFile(string filename);
};

#endif
