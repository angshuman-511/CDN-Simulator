#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;

namespace Utils
{
    void printBanner();
    void printSeparator(char ch = '=', int length = 60);
    void printMenu();
    void simulateLatency(int ms);
    string getCurrentTimestamp();
    void printColored(string text, string color);
}

#endif
