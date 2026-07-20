#include "Client.h"

Client::Client(int id, string city)
{
    this->clientId = id;
    this->city = city;
}

Client::Client(string city)
{
    this->clientId = 0;
    this->city = city;
}

int Client::getId()
{
    return clientId;
}

string Client::getCity()
{
    return city;
}

string Client::requestFile(string filename)
{
    cout << "  [Client " << clientId << " @ " << city << "] Requesting: " << filename << endl;
    return filename;
}