#include "Statistics.h"

Statistics::Statistics()
{
    totalRequests = 0;
    hits = 0;
    misses = 0;
    errors = 0;
}

void Statistics::addHit()
{
    totalRequests++;
    hits++;
}

void Statistics::addMiss()
{
    totalRequests++;
    misses++;
}

void Statistics::addError()
{
    totalRequests++;
    errors++;
}

int Statistics::getTotalRequests()
{
    return totalRequests;
}

int Statistics::getHits()
{
    return hits;
}

int Statistics::getMisses()
{
    return misses;
}

double Statistics::getHitRate()
{
    if (totalRequests == 0) return 0.0;
    return (double)hits / totalRequests * 100.0;
}

void Statistics::logRequest(string timestamp, string city, string filename, string result, int edgeId)
{
    RequestLog log;
    log.timestamp = timestamp;
    log.clientCity = city;
    log.filename = filename;
    log.result = result;
    log.edgeServerId = edgeId;
    requestLogs.push_back(log);
}

void Statistics::print()
{
    cout << endl;
    cout << "  ╔══════════════════════════════════════╗" << endl;
    cout << "  ║         CDN STATISTICS REPORT        ║" << endl;
    cout << "  ╠══════════════════════════════════════╣" << endl;
    cout << "  ║  Total Requests : " << setw(8) << totalRequests << "           ║" << endl;
    cout << "  ║  Cache Hits     : " << setw(8) << hits << "  ✓        ║" << endl;
    cout << "  ║  Cache Misses   : " << setw(8) << misses << "  ✗        ║" << endl;
    cout << "  ║  Errors         : " << setw(8) << errors << "  !        ║" << endl;
    cout << "  ║  Hit Rate       : " << setw(7) << fixed << setprecision(1) << getHitRate() << "%           ║" << endl;
    cout << "  ╚══════════════════════════════════════╝" << endl;
    cout << endl;
}

void Statistics::printLog()
{
    if (requestLogs.empty())
    {
        cout << "  No requests logged yet." << endl;
        return;
    }

    cout << endl;
    cout << "  " << string(78, '-') << endl;
    cout << "  " << left << setw(22) << "Timestamp"
         << setw(14) << "City"
         << setw(20) << "File"
         << setw(10) << "Result"
         << setw(10) << "Edge ID" << endl;
    cout << "  " << string(78, '-') << endl;

    for (auto& log : requestLogs)
    {
        cout << "  " << left << setw(22) << log.timestamp
             << setw(14) << log.clientCity
             << setw(20) << log.filename
             << setw(10) << log.result
             << setw(10) << log.edgeServerId << endl;
    }

    cout << "  " << string(78, '-') << endl;
    cout << "  Total: " << requestLogs.size() << " request(s)" << endl;
    cout << endl;
}

void Statistics::reset()
{
    totalRequests = 0;
    hits = 0;
    misses = 0;
    errors = 0;
    requestLogs.clear();
    cout << "  Statistics reset." << endl;
}