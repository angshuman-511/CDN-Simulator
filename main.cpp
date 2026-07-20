#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "OriginServer.h"
#include "EdgeServer.h"
#include "Router.h"
#include "Client.h"
#include "Statistics.h"
#include "Utils.h"

using namespace std;

void handleRequest(string city, string filename, OriginServer& origin,
                   map<int, EdgeServer*>& edges, Router& router, Statistics& stats);
void runBatchSimulation(OriginServer& origin, map<int, EdgeServer*>& edges,
                        Router& router, Statistics& stats);

int main()
{
    OriginServer origin;
    origin.addFile("logo.png", "PNG image data - company logo 256x256px");
    origin.addFile("home.html", "<!DOCTYPE html><html><body>Welcome to CDN Sim</body></html>");
    origin.addFile("video.mp4", "MP4 video stream data - 1080p promotional video");
    origin.addFile("style.css", "body { font-family: Arial; margin: 0; padding: 20px; }");
    origin.addFile("app.js", "function init() { console.log('App initialized'); }");
    origin.addFile("data.json", "{ \"users\": 1500, \"active\": 320, \"cdn_nodes\": 3 }");
    origin.addFile("banner.jpg", "JPEG image data - hero banner 1920x600px");
    origin.addFile("api.php", "<?php echo json_encode(['status' => 'ok']); ?>");
    EdgeServer edge1(1, "Mumbai", 5);
    EdgeServer edge2(2, "Delhi", 5);
    EdgeServer edge3(3, "Bangalore", 5);
    map<int, EdgeServer*> edges;
    edges[1] = &edge1;
    edges[2] = &edge2;
    edges[3] = &edge3;
    Router router;
    router.addRoute("Mumbai", 1);
    router.addRoute("Pune", 1);
    router.addRoute("Goa", 1);
    router.addRoute("Delhi", 2);
    router.addRoute("Jaipur", 2);
    router.addRoute("Lucknow", 2);
    router.addRoute("Bangalore", 3);
    router.addRoute("Chennai", 3);
    router.addRoute("Hyderabad", 3);
    Statistics stats;

    Utils::printBanner();

    cout << "  Origin Server loaded with " << 8 << " files." << endl;
    cout << "  3 Edge Servers deployed: Mumbai, Delhi, Bangalore" << endl;
    cout << "  9 cities configured in routing table." << endl;
    cout << "  Cache capacity: 5 files per edge (LRU eviction)" << endl;
    int choice;
    bool running = true;

    while (running)
    {
        Utils::printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string city, filename;
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  FILE REQUEST" << endl;
                Utils::printSeparator('-', 50);
                cout << "  Available cities: Mumbai, Pune, Goa, Delhi, Jaipur," << endl;
                cout << "                    Lucknow, Bangalore, Chennai, Hyderabad" << endl;
                cout << "  Enter client city: ";
                cin >> city;
                cout << "  Enter filename: ";
                cin >> filename;
                cout << endl;

                handleRequest(city, filename, origin, edges, router, stats);
                break;
            }

            case 2:
            {
                string name, content;
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  ADD FILE TO ORIGIN SERVER" << endl;
                Utils::printSeparator('-', 50);
                cout << "  Enter filename: ";
                cin >> name;
                cout << "  Enter content: ";
                cin.ignore();
                getline(cin, content);

                origin.addFile(name, content);
                cout << "  [Origin] File added: " << name << endl;
                break;
            }

            case 3:
            {
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  EDGE SERVER CACHE STATUS" << endl;
                Utils::printSeparator('-', 50);
                edge1.printCache();
                cout << endl;
                edge2.printCache();
                cout << endl;
                edge3.printCache();
                break;
            }

            case 4:
            {
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  ORIGIN SERVER FILES" << endl;
                Utils::printSeparator('-', 50);
                origin.printFiles();
                break;
            }

            case 5:
            {
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  PERFORMANCE METRICS" << endl;
                Utils::printSeparator('-', 50);
                stats.print();
                stats.printLog();
                break;
            }

            case 6:
            {
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  CDN ROUTING TABLE" << endl;
                Utils::printSeparator('-', 50);
                router.printRoutes();
                break;
            }

            case 7:
            {
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  BATCH SIMULATION" << endl;
                Utils::printSeparator('-', 50);
                runBatchSimulation(origin, edges, router, stats);
                break;
            }

            case 8:
            {
                cout << endl;
                Utils::printSeparator('-', 50);
                cout << "  CLEARING ALL CACHES" << endl;
                Utils::printSeparator('-', 50);
                edge1.clearCache();
                edge2.clearCache();
                edge3.clearCache();
                cout << "  All edge server caches cleared." << endl;
                break;
            }

            case 9:
            {
                cout << endl;
                stats.reset();
                break;
            }

            case 0:
            {
                cout << endl;
                Utils::printSeparator('=', 50);
                cout << "  Final Statistics:" << endl;
                stats.print();
                cout << "  CDN Simulator terminated. Goodbye!" << endl;
                Utils::printSeparator('=', 50);
                cout << endl;
                running = false;
                break;
            }

            default:
            {
                cout << "  Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}


void handleRequest(string city, string filename, OriginServer& origin,
                   map<int, EdgeServer*>& edges, Router& router, Statistics& stats)
{
    string timestamp = Utils::getCurrentTimestamp();

    cout << "  ┌─── REQUEST PROCESSING ───────────────────────┐" << endl;
    cout << "  │ City: " << city << endl;
    cout << "  │ File: " << filename << endl;
    cout << "  └──────────────────────────────────────────────┘" << endl;

    cout << "  [Router] Looking up nearest edge for " << city << "..." << endl;
    Utils::simulateLatency(50);

    int edgeId = router.getNearestEdge(city);

    if (edgeId == -1)
    {
        cout << "  [Router] ERROR: No route found for city '" << city << "'" << endl;
        stats.addError();
        stats.logRequest(timestamp, city, filename, "ERROR", -1);
        return;
    }

    EdgeServer* edge = edges[edgeId];
    cout << "  [Router] Routed to Edge Server " << edgeId
         << " (" << edge->getRegion() << ")" << endl;

    cout << "  [Edge " << edgeId << "] Checking cache for '" << filename << "'..." << endl;
    Utils::simulateLatency(30);

    if (edge->hasFile(filename))
    {
        string content = edge->getFile(filename);
        Utils::simulateLatency(20);

        Utils::printColored("  >> CACHE HIT! ", "green");
        cout << "Served from Edge " << edgeId << " (" << edge->getRegion() << ")" << endl;
        cout << "  >> Content: \"" << content.substr(0, 50)
             << (content.length() > 50 ? "..." : "") << "\"" << endl;
        cout << "  >> Latency: ~5ms (edge cache)" << endl;

        stats.addHit();
        stats.logRequest(timestamp, city, filename, "HIT", edgeId);
    }
    else
    {
        cout << "  [Edge " << edgeId << "] Cache MISS. Fetching from Origin Server..." << endl;
        Utils::simulateLatency(150);

        if (origin.hasFile(filename))
        {
            string content = origin.getFile(filename);

            edge->storeFile(filename, content);

            Utils::printColored("  >> CACHE MISS ", "yellow");
            cout << "- Fetched from Origin and cached on Edge " << edgeId << endl;
            cout << "  >> Content: \"" << content.substr(0, 50)
                 << (content.length() > 50 ? "..." : "") << "\"" << endl;
            cout << "  >> Latency: ~100ms (origin fetch)" << endl;

            stats.addMiss();
            stats.logRequest(timestamp, city, filename, "MISS", edgeId);
        }
        else
        {
            Utils::printColored("  >> ERROR: ", "red");
            cout << "File '" << filename << "' not found on Origin Server!" << endl;
            cout << "  >> Latency: ~150ms (origin lookup + failure)" << endl;

            stats.addError();
            stats.logRequest(timestamp, city, filename, "ERROR", edgeId);
        }
    }
    cout << endl;
}


void runBatchSimulation(OriginServer& origin, map<int, EdgeServer*>& edges,
                        Router& router, Statistics& stats)
{
    ifstream file("data/files.txt");

    if (!file.is_open())
    {
        cout << "  ERROR: Could not open data/files.txt" << endl;
        cout << "  Make sure the file exists with format: City Filename" << endl;
        return;
    }

    string line;
    int requestCount = 0;

    cout << "  Loading batch requests from data/files.txt..." << endl;
    cout << endl;

    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line);
        string city, filename;

        if (iss >> city >> filename)
        {
            requestCount++;
            cout << "  ━━━ Batch Request #" << requestCount << " ━━━" << endl;
            handleRequest(city, filename, origin, edges, router, stats);
        }
    }

    file.close();

    cout << endl;
    Utils::printSeparator('=', 50);
    cout << "  Batch simulation complete: " << requestCount << " request(s) processed." << endl;
    Utils::printSeparator('=', 50);
}

// g++ -std=c++17 -o cdn_sim.exe main.cpp Client.cpp Cache.cpp EdgeServer.cpp OriginServer.cpp Router.cpp Statistics.cpp Utils.cpp
// .\cdn_sim.exe         <- for run use this command