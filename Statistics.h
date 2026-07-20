#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct RequestLog
{
    string timestamp;
    string clientCity;
    string filename;
    string result;   // "HIT", "MISS", "ERROR"
    int edgeServerId;
};

class Statistics
{
private:
    int totalRequests;
    int hits;
    int misses;
    int errors;
    vector<RequestLog> requestLogs;

public:
    Statistics();

    void addHit();
    void addMiss();
    void addError();

    int getTotalRequests();
    int getHits();
    int getMisses();
    double getHitRate();

    void logRequest(string timestamp, string city, string filename, string result, int edgeId);

    void print();
    void printLog();
    void reset();
};

#endif
