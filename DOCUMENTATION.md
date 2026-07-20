# 📖 CDN Simulator — Complete Documentation

> **Audience**: Beginners learning C++. This document explains **every single file** in the project, line by line, so you understand not just *what* the code does, but *why* it does it.

---

## 📑 Table of Contents

1. [What is a CDN?](#-what-is-a-cdn)
2. [Project Overview](#-project-overview)
3. [How the Files are Organized](#-how-the-files-are-organized)
4. [Architecture Diagram](#-architecture-diagram)
5. [File-by-File Explanation](#-file-by-file-explanation)
   - [Cache.h](#1%EF%B8%8F⃣-cacheh--the-cache-blueprint)
   - [Cache.cpp](#2%EF%B8%8F⃣-cachecpp--the-cache-brain)
   - [Client.h](#3%EF%B8%8F⃣-clienth--the-client-blueprint)
   - [Client.cpp](#4%EF%B8%8F⃣-clientcpp--the-client-logic)
   - [EdgeServer.h](#5%EF%B8%8F⃣-edgeserverh--the-edge-server-blueprint)
   - [EdgeServer.cpp](#6%EF%B8%8F⃣-edgeservercpp--the-edge-server-logic)
   - [OriginServer.h](#7%EF%B8%8F⃣-originserverh--the-origin-server-blueprint)
   - [OriginServer.cpp](#8%EF%B8%8F⃣-originservercpp--the-origin-server-logic)
   - [Router.h](#9%EF%B8%8F⃣-routerh--the-router-blueprint)
   - [Router.cpp](#🔟-routercpp--the-router-logic)
   - [Statistics.h](#1%EF%B8%8F⃣1%EF%B8%8F⃣-statisticsh--the-statistics-blueprint)
   - [Statistics.cpp](#1%EF%B8%8F⃣2%EF%B8%8F⃣-statisticscpp--the-statistics-logic)
   - [Utils.h](#1%EF%B8%8F⃣3%EF%B8%8F⃣-utilsh--the-utilities-blueprint)
   - [Utils.cpp](#1%EF%B8%8F⃣4%EF%B8%8F⃣-utilscpp--the-utilities-logic)
   - [main.cpp](#1%EF%B8%8F⃣5%EF%B8%8F⃣-maincpp--the-main-program)
   - [data/files.txt](#1%EF%B8%8F⃣6%EF%B8%8F⃣-datafilestxt--batch-request-data)
6. [How a Request Flows Through the System](#-how-a-request-flows-through-the-system)
7. [How to Build and Run](#-how-to-build-and-run)
8. [Glossary of C++ Concepts](#-glossary-of-c-concepts)

---

## 🌐 What is a CDN?

A **CDN (Content Delivery Network)** is a system of servers spread across different locations that deliver web content (images, videos, web pages) to users faster.

### Real-World Analogy

Imagine a pizza chain:
- **Origin Server** = The central kitchen where all recipes are stored
- **Edge Servers** = Local branches in different cities
- **Cache** = Pizzas already prepared at the local branch
- **Router** = The system that sends your order to the nearest branch
- **Client** = You, the customer

**Without a CDN**: Every pizza order goes to the central kitchen (slow! 🐌)
**With a CDN**: Your order goes to the nearest branch. If they have it ready (cache hit ✅), you get it instantly. If not (cache miss ❌), they get the recipe from the central kitchen, make it, and keep a copy for next time.

```
                    ┌──────────────┐
                    │ Origin Server │  ← Central storage (all files live here)
                    │   (Delhi)     │
                    └──────┬───────┘
                           │
              ┌────────────┼────────────┐
              │            │            │
        ┌─────┴─────┐ ┌───┴──────┐ ┌───┴──────────┐
        │ Edge Srv 1 │ │ Edge Srv 2│ │  Edge Srv 3  │
        │  (Mumbai)  │ │  (Delhi)  │ │ (Bangalore)  │
        │ Cache: 5   │ │ Cache: 5  │ │  Cache: 5    │
        └─────┬──────┘ └────┬─────┘ └──────┬───────┘
              │             │              │
        ┌─────┴──┐    ┌────┴────┐    ┌────┴────────┐
        │Mumbai  │    │Delhi    │    │Bangalore    │
        │Pune    │    │Jaipur   │    │Chennai      │
        │Goa     │    │Lucknow  │    │Hyderabad    │
        └────────┘    └─────────┘    └─────────────┘
         Clients        Clients         Clients
```

---

## 🏗 Project Overview

This project simulates a CDN using **C++ classes**. Each real-world component is represented by a C++ class:

| Real World | C++ Class | File |
|---|---|---|
| Central storage server | `OriginServer` | OriginServer.h / .cpp |
| Local branch server | `EdgeServer` | EdgeServer.h / .cpp |
| Storage at each branch | `Cache` | Cache.h / .cpp |
| Order routing system | `Router` | Router.h / .cpp |
| Customer | `Client` | Client.h / .cpp |
| Analytics dashboard | `Statistics` | Statistics.h / .cpp |
| Helper tools | `Utils` namespace | Utils.h / .cpp |
| The main program | `main()` function | main.cpp |
| Test data | Text file | data/files.txt |

---

## 📂 How the Files are Organized

```
CDN Simulator/
│
├── main.cpp              ← 🚀 Entry point: runs the entire simulation
│
├── Cache.h               ← 📋 Blueprint for the Cache class
├── Cache.cpp             ← ⚙️ Implementation of Cache methods
│
├── Client.h              ← 📋 Blueprint for the Client class
├── Client.cpp            ← ⚙️ Implementation of Client methods
│
├── EdgeServer.h          ← 📋 Blueprint for the EdgeServer class
├── EdgeServer.cpp        ← ⚙️ Implementation of EdgeServer methods
│
├── OriginServer.h        ← 📋 Blueprint for the OriginServer class
├── OriginServer.cpp      ← ⚙️ Implementation of OriginServer methods
│
├── Router.h              ← 📋 Blueprint for the Router class
├── Router.cpp            ← ⚙️ Implementation of Router methods
│
├── Statistics.h          ← 📋 Blueprint for the Statistics class
├── Statistics.cpp        ← ⚙️ Implementation of Statistics methods
│
├── Utils.h               ← 📋 Declarations for utility functions
├── Utils.cpp             ← ⚙️ Implementation of utility functions
│
└── data/
    └── files.txt         ← 📄 Sample batch requests for testing
```

> [!TIP]
> **Why two files per class?** In C++, we separate the **declaration** (`.h` file — *what* the class can do) from the **definition** (`.cpp` file — *how* it does it). Think of `.h` as the restaurant menu and `.cpp` as the kitchen that actually makes the food.

---

## 🔀 Architecture Diagram

Here's how all the classes interact when a user requests a file:

```
  ┌──────────┐     ┌──────────┐     ┌──────────────┐     ┌──────────────┐
  │  Client   │────►│  Router   │────►│  EdgeServer   │────►│ OriginServer │
  │ (user)    │     │ (lookup)  │     │  (cache)      │     │ (storage)    │
  └──────────┘     └──────────┘     └──────────────┘     └──────────────┘
                                           │
                                           ▼
                                    ┌──────────────┐
                                    │    Cache      │
                                    │ (LRU storage) │
                                    └──────────────┘

  Every request is recorded by:
                                    ┌──────────────┐
                                    │  Statistics   │
                                    │ (analytics)   │
                                    └──────────────┘
```

**Flow of a request:**
1. A **Client** from a city wants a file
2. The **Router** finds the nearest **EdgeServer** for that city
3. The **EdgeServer** checks its **Cache**
4. **Cache HIT** → File is returned immediately (fast! ⚡)
5. **Cache MISS** → EdgeServer fetches from **OriginServer**, stores in Cache, then returns
6. **Statistics** logs every request as HIT, MISS, or ERROR

---

## 📝 File-by-File Explanation

---

### 1️⃣ Cache.h — The Cache Blueprint

📍 **File**: [Cache.h](file:///d:/CDN%20Simulator/Cache.h)
🎯 **Purpose**: Declares the `Cache` class — a storage with limited space that remembers recently used files.

```cpp
#ifndef CACHE_H          // ← "Include guard": prevents this file from being
#define CACHE_H          //    included twice (which would cause errors)

#include <iostream>       // ← For cout (printing to screen)
#include <unordered_map>  // ← For hash map (fast key→value lookups)
#include <list>           // ← For doubly-linked list (used for LRU tracking)
#include <string>         // ← For the string data type

using namespace std;      // ← So we can write "string" instead of "std::string"
```

**The class declaration:**

```cpp
class Cache
{
private:
    int capacity;
    // ↑ Maximum number of files this cache can hold (e.g., 5)

    list<string> accessOrder;
    // ↑ A list that tracks which files were used recently.
    //   Front = most recently used, Back = least recently used.
    //   This is the heart of the LRU (Least Recently Used) algorithm.

    unordered_map<string, string> files;
    // ↑ The actual storage: filename → file content
    //   Example: "logo.png" → "PNG image data..."

    unordered_map<string, list<string>::iterator> iteratorMap;
    // ↑ Stores a "pointer" to each file's position in the accessOrder list.
    //   This allows us to move any file to the front in O(1) time.
    //   Without this, we'd have to search the entire list (slow!).

    void evict();
    // ↑ Private method: removes the least recently used file when cache is full

public:
    Cache(int size = 5);          // Constructor: creates a cache with given capacity
    bool contains(string file);    // Does this file exist in the cache?
    string get(string file);       // Get a file's content from cache
    void put(string file, string content); // Store a file in cache
    void clear();                  // Remove everything from cache
    int getSize();                 // How many files are currently cached?
    int getCapacity();             // What's the maximum capacity?
    void printContents();          // Display what's in the cache
};
```

> [!NOTE]
> **What is LRU?** LRU stands for "Least Recently Used". When the cache is full and a new file needs to be stored, the file that hasn't been accessed for the longest time gets removed. It's like a bookshelf with limited space — when it's full, you remove the book you haven't read in the longest time.

---

### 2️⃣ Cache.cpp — The Cache Brain

📍 **File**: [Cache.cpp](file:///d:/CDN%20Simulator/Cache.cpp)
🎯 **Purpose**: Implements all the `Cache` methods declared in `Cache.h`.

#### Constructor
```cpp
#include "Cache.h"   // ← Include the blueprint

Cache::Cache(int size)
{
    capacity = size;  // ← Set the max number of files this cache can hold
}
```

#### contains() — Check if a file is in the cache
```cpp
bool Cache::contains(string file)
{
    return files.find(file) != files.end();
    // ↑ Search for the file in our hash map.
    //   find() returns an "iterator" pointing to the file if found,
    //   or end() if not found. So if it's NOT end(), the file exists.
}
```

#### get() — Retrieve a file from the cache
```cpp
string Cache::get(string file)
{
    if (!contains(file))       // If file doesn't exist in cache...
    {
        return "";             // ...return empty string
    }

    // LRU: Move this file to the FRONT of accessOrder (it's now "most recent")
    accessOrder.erase(iteratorMap[file]);   // Remove from current position
    accessOrder.push_front(file);           // Add to front
    iteratorMap[file] = accessOrder.begin(); // Update the pointer

    return files[file];  // Return the file content
}
```

> [!TIP]
> **Why move to front on get()?** Every time you access a file, it proves the file is "useful". By moving it to the front, we protect it from being evicted. The files at the back (not accessed recently) are the first to be removed.

#### put() — Store a file in the cache
```cpp
void Cache::put(string file, string content)
{
    // Case 1: File already exists → just update it
    if (contains(file))
    {
        files[file] = content;                     // Update content
        accessOrder.erase(iteratorMap[file]);       // Remove from old position
        accessOrder.push_front(file);               // Move to front (most recent)
        iteratorMap[file] = accessOrder.begin();    // Update pointer
        return;
    }

    // Case 2: Cache is full → evict the least recently used file
    if ((int)files.size() >= capacity)
    {
        evict();  // Remove the oldest file to make room
    }

    // Case 3: Insert the new file
    files[file] = content;                     // Store the content
    accessOrder.push_front(file);               // Add to front (most recent)
    iteratorMap[file] = accessOrder.begin();    // Save pointer for fast access later
}
```

#### evict() — Remove the least recently used file
```cpp
void Cache::evict()
{
    if (accessOrder.empty()) return;  // Nothing to evict

    string lruFile = accessOrder.back();  // The LAST item = least recently used
    accessOrder.pop_back();               // Remove from access order list
    files.erase(lruFile);                 // Remove from storage
    iteratorMap.erase(lruFile);           // Remove the pointer

    cout << "    [Cache] Evicted (LRU): " << lruFile << endl;  // Tell the user
}
```

#### Utility methods
```cpp
void Cache::clear()         // Remove everything
{
    files.clear();
    accessOrder.clear();
    iteratorMap.clear();
}

int Cache::getSize()        { return (int)files.size(); }  // Current count
int Cache::getCapacity()    { return capacity; }            // Max capacity

void Cache::printContents()  // Display all cached files
{
    if (files.empty()) { cout << "    (empty)" << endl; return; }

    cout << "    Capacity: " << getSize() << "/" << capacity << endl;
    int index = 1;
    for (auto& file : accessOrder)  // Loop through files in access order
    {
        cout << "    " << index << ". " << file
             << " (" << files[file].length() << " bytes)"
             << (index == 1 ? " [Most Recent]" : "")
             << (index == (int)accessOrder.size() ? " [Least Recent]" : "")
             << endl;
        index++;
    }
}
```

> [!IMPORTANT]
> **The LRU algorithm uses 3 data structures working together:**
> | Data Structure | Type | Purpose |
> |---|---|---|
> | `files` | `unordered_map<string, string>` | Stores actual file content |
> | `accessOrder` | `list<string>` | Tracks usage order (front=newest, back=oldest) |
> | `iteratorMap` | `unordered_map<string, iterator>` | Fast pointer to each file's position in the list |
>
> This combination gives us **O(1)** time for get, put, and evict operations!

---

### 3️⃣ Client.h — The Client Blueprint

📍 **File**: [Client.h](file:///d:/CDN%20Simulator/Client.h)
🎯 **Purpose**: Represents a user who requests files from the CDN.

```cpp
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

using namespace std;

class Client
{
private:
    int clientId;    // ← Unique number to identify this client (e.g., 1, 2, 3)
    string city;     // ← The city where this client is located (e.g., "Mumbai")

public:
    Client(int id, string city);   // Constructor with ID and city
    Client(string city);           // Constructor with just city (ID defaults to 0)

    int getId();                    // Get the client's ID
    string getCity();               // Get the client's city
    string requestFile(string filename); // Client requests a file
};

#endif
```

> [!NOTE]
> **Two constructors?** This is called **constructor overloading**. You can create a Client two ways:
> - `Client c1(1, "Mumbai");` — with an ID
> - `Client c2("Delhi");` — without an ID (defaults to 0)

---

### 4️⃣ Client.cpp — The Client Logic

📍 **File**: [Client.cpp](file:///d:/CDN%20Simulator/Client.cpp)
🎯 **Purpose**: Implements all `Client` methods.

```cpp
#include "Client.h"

// Constructor 1: with ID and city
Client::Client(int id, string city)
{
    this->clientId = id;    // "this->" distinguishes the class variable
    this->city = city;      //  from the parameter with the same name
}

// Constructor 2: with just city
Client::Client(string city)
{
    this->clientId = 0;     // Default ID
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
    // Print a message showing who is requesting what
    cout << "  [Client " << clientId << " @ " << city
         << "] Requesting: " << filename << endl;
    return filename;  // Return the filename (the actual fetching is done elsewhere)
}
```

> [!TIP]
> **What is `this->`?** It's a pointer to the current object. When the parameter name (`city`) is the same as the class variable name (`city`), we use `this->city` to mean "the class's city variable" and just `city` for the parameter.

---

### 5️⃣ EdgeServer.h — The Edge Server Blueprint

📍 **File**: [EdgeServer.h](file:///d:/CDN%20Simulator/EdgeServer.h)
🎯 **Purpose**: Represents a server close to users that has its own cache.

```cpp
#ifndef EDGE_SERVER_H
#define EDGE_SERVER_H

#include <iostream>
#include <string>
#include "Cache.h"         // ← EdgeServer USES a Cache, so we include it

using namespace std;

class EdgeServer
{
private:
    int id;                // ← Server ID (1, 2, or 3)
    string region;         // ← Region name (e.g., "Mumbai")
    Cache cache;           // ← Each edge server HAS its own cache
    //    ↑ This is called "composition" — the EdgeServer contains a Cache object

public:
    EdgeServer(int id, string region = "Default", int cacheCapacity = 5);
    //         ↑ Default region is "Default", default cache size is 5

    bool hasFile(string filename);           // Is this file in my cache?
    string getFile(string filename);         // Get file from my cache
    void storeFile(string filename, string content); // Store file in my cache
    int getID();                             // Get my server ID
    string getRegion();                      // Get my region name
    void clearCache();                       // Empty my cache
    void printCache();                       // Display my cache contents
};

#endif
```

> [!NOTE]
> **Composition**: The line `Cache cache;` means every `EdgeServer` automatically contains a `Cache` object inside it. When the EdgeServer is created, the Cache is created too. When the EdgeServer is destroyed, the Cache is destroyed too. This is one of the most important relationships in Object-Oriented Programming.

---

### 6️⃣ EdgeServer.cpp — The Edge Server Logic

📍 **File**: [EdgeServer.cpp](file:///d:/CDN%20Simulator/EdgeServer.cpp)
🎯 **Purpose**: Implements all `EdgeServer` methods. Notice how most methods simply **delegate** (pass the work) to the internal `cache` object.

```cpp
#include "EdgeServer.h"

// Constructor: uses an "initializer list" to set up member variables
EdgeServer::EdgeServer(int id, string region, int cacheCapacity)
    : id(id), region(region), cache(cacheCapacity)
    // ↑ This is called an "initializer list" — it sets values BEFORE
    //   the constructor body runs. It's required here because Cache
    //   needs a parameter (cacheCapacity) to be constructed.
{
    // Constructor body is empty because everything is set up above
}

// All these methods just pass the work to the cache:
bool EdgeServer::hasFile(string filename)
{
    return cache.contains(filename);   // Ask the cache
}

string EdgeServer::getFile(string filename)
{
    return cache.get(filename);        // Get from cache
}

void EdgeServer::storeFile(string filename, string content)
{
    cache.put(filename, content);      // Store in cache
}

int EdgeServer::getID()       { return id; }
string EdgeServer::getRegion() { return region; }

void EdgeServer::clearCache()
{
    cache.clear();
    cout << "  [Edge " << id << " - " << region << "] Cache cleared." << endl;
}

void EdgeServer::printCache()
{
    cout << "  Edge Server " << id << " (" << region << ") - Cache:" << endl;
    cache.printContents();   // Delegate to cache's print method
}
```

> [!TIP]
> **What is an initializer list?** The `: id(id), region(region), cache(cacheCapacity)` syntax before the constructor body `{}` initializes member variables. It's more efficient than assigning inside the body, and it's **required** when a member (like `cache`) needs constructor arguments.

---

### 7️⃣ OriginServer.h — The Origin Server Blueprint

📍 **File**: [OriginServer.h](file:///d:/CDN%20Simulator/OriginServer.h)
🎯 **Purpose**: The central storage server that holds ALL files. This is the "source of truth" for the entire CDN.

```cpp
#ifndef ORIGIN_SERVER_H
#define ORIGIN_SERVER_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class OriginServer
{
private:
    unordered_map<string, string> files;
    // ↑ Stores ALL files: filename → content
    //   Unlike the Cache, this has UNLIMITED capacity
    //   (no eviction needed — the origin keeps everything forever)

public:
    void addFile(string name, string content);  // Upload a file to the server
    bool hasFile(string name);                   // Does this file exist?
    string getFile(string name);                 // Download a file
    int getFileCount();                          // How many files are stored?
    void printFiles();                           // List all files
};

#endif
```

> [!NOTE]
> **Key difference from Cache**: The `OriginServer` has **no capacity limit** and **no eviction**. It stores everything permanently. In real life, this would be a massive data center with terabytes of storage.

---

### 8️⃣ OriginServer.cpp — The Origin Server Logic

📍 **File**: [OriginServer.cpp](file:///d:/CDN%20Simulator/OriginServer.cpp)
🎯 **Purpose**: Implements the origin server methods. These are straightforward hash map operations.

```cpp
#include "OriginServer.h"

void OriginServer::addFile(string name, string content)
{
    files[name] = content;
    // ↑ The [] operator on unordered_map inserts if the key doesn't exist,
    //   or updates if it does. Simple and clean!
}

bool OriginServer::hasFile(string name)
{
    return files.find(name) != files.end();
    // ↑ Same pattern as Cache::contains()
    //   find() returns end() if not found
}

string OriginServer::getFile(string name)
{
    return files[name];
    // ↑ Returns the content. If the file doesn't exist, this returns
    //   an empty string (default for unordered_map)
}

int OriginServer::getFileCount()
{
    return (int)files.size();
    // ↑ size() returns size_t (unsigned), we cast to int for safety
}

void OriginServer::printFiles()
{
    if (files.empty())
    {
        cout << "  (no files on origin)" << endl;
        return;
    }

    cout << "  Origin Server Files (" << files.size() << " total):" << endl;
    int index = 1;
    for (auto& pair : files)    // "auto&" automatically detects the type
    {                           // Each "pair" has .first (key) and .second (value)
        cout << "    " << index << ". " << pair.first
             << " (" << pair.second.length() << " bytes)" << endl;
        index++;
    }
}
```

> [!TIP]
> **`auto& pair`** — The `auto` keyword tells C++ to figure out the type automatically. The `&` means "by reference" (don't make a copy, use the original). Each element in an `unordered_map` is a `pair` with `.first` (the key/filename) and `.second` (the value/content).

---

### 9️⃣ Router.h — The Router Blueprint

📍 **File**: [Router.h](file:///d:/CDN%20Simulator/Router.h)
🎯 **Purpose**: Maps cities to their nearest edge server. When a client from Mumbai makes a request, the Router says "send it to Edge Server 1".

```cpp
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
    // ↑ Maps city name → edge server ID
    //   Example: "Mumbai" → 1, "Delhi" → 2, "Bangalore" → 3

public:
    Router();                                    // Constructor
    void addRoute(string city, int edgeId);      // Register a city→edge mapping
    int getNearestEdge(string city);             // Find the nearest edge for a city
    bool hasRoute(string city);                  // Is this city registered?
    void printRoutes();                          // Display the routing table
};

#endif
```

---

### 🔟 Router.cpp — The Router Logic

📍 **File**: [Router.cpp](file:///d:/CDN%20Simulator/Router.cpp)
🎯 **Purpose**: Implements the routing logic — simple hash map lookups.

```cpp
#include "Router.h"

Router::Router()
{
    // Empty constructor — the routing table starts empty
    // Routes are added later using addRoute()
}

void Router::addRoute(string city, int edgeId)
{
    cityToEdge[city] = edgeId;
    // ↑ Add or update the mapping: "Mumbai" → 1
}

int Router::getNearestEdge(string city)
{
    if (cityToEdge.find(city) != cityToEdge.end())
    {
        return cityToEdge[city];   // Found! Return the edge server ID
    }
    return -1;  // City not found → return -1 as error code
    // ↑ Using -1 as a "sentinel value" to indicate failure
    //   The caller must check for -1 and handle the error
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
        cout << "    " << pair.first << " --> Edge Server "
             << pair.second << endl;
    }
}
```

> [!NOTE]
> **Routing table configuration for this simulator:**
> | City | Nearest Edge Server |
> |---|---|
> | Mumbai, Pune, Goa | Edge 1 (Mumbai) |
> | Delhi, Jaipur, Lucknow | Edge 2 (Delhi) |
> | Bangalore, Chennai, Hyderabad | Edge 3 (Bangalore) |

---

### 1️⃣1️⃣ Statistics.h — The Statistics Blueprint

📍 **File**: [Statistics.h](file:///d:/CDN%20Simulator/Statistics.h)
🎯 **Purpose**: Tracks how well the CDN is performing — counts hits, misses, errors, and logs every request.

```cpp
#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <string>
#include <vector>     // ← Dynamic array to store request logs
#include <iomanip>    // ← For formatting output (setw, setprecision)

using namespace std;

// A struct is like a simple class where everything is public by default
struct RequestLog
{
    string timestamp;      // When the request happened (e.g., "2026-07-20 21:00:00")
    string clientCity;     // Which city the request came from
    string filename;       // Which file was requested
    string result;         // "HIT", "MISS", or "ERROR"
    int edgeServerId;      // Which edge server handled it
};

class Statistics
{
private:
    int totalRequests;     // Total number of requests made
    int hits;              // How many times the file was found in cache
    int misses;            // How many times the file was NOT in cache
    int errors;            // How many requests failed
    vector<RequestLog> requestLogs;  // Detailed log of every request
    // ↑ A vector is like an array that can grow dynamically

public:
    Statistics();

    void addHit();         // Record a cache hit
    void addMiss();        // Record a cache miss
    void addError();       // Record an error

    int getTotalRequests();
    int getHits();
    int getMisses();
    double getHitRate();   // Calculate hit rate as percentage

    void logRequest(string timestamp, string city, string filename,
                    string result, int edgeId);  // Log detailed request info

    void print();          // Print the statistics summary box
    void printLog();       // Print the detailed request log table
    void reset();          // Reset all statistics to zero
};

#endif
```

> [!NOTE]
> **struct vs class**: A `struct` is almost identical to a `class` in C++. The only difference is that members are `public` by default in a struct and `private` by default in a class. Structs are commonly used for simple data containers (like `RequestLog`), while classes are used for objects with complex behavior.

---

### 1️⃣2️⃣ Statistics.cpp — The Statistics Logic

📍 **File**: [Statistics.cpp](file:///d:/CDN%20Simulator/Statistics.cpp)
🎯 **Purpose**: Implements all statistics tracking and display methods.

#### Constructor and Counter methods
```cpp
#include "Statistics.h"

Statistics::Statistics()
{
    totalRequests = 0;   // Start with zero everything
    hits = 0;
    misses = 0;
    errors = 0;
}

void Statistics::addHit()   { totalRequests++; hits++; }
void Statistics::addMiss()  { totalRequests++; misses++; }
void Statistics::addError() { totalRequests++; errors++; }
// ↑ Each method increments totalRequests AND its specific counter
```

#### Hit Rate Calculation
```cpp
double Statistics::getHitRate()
{
    if (totalRequests == 0) return 0.0;  // Avoid division by zero!
    return (double)hits / totalRequests * 100.0;
    //     ↑ Cast to double for decimal division
    //       Without cast: 7/25 = 0 (integer division truncates)
    //       With cast: 7.0/25 = 0.28 → × 100 = 28.0%
}
```

> [!IMPORTANT]
> **Division by zero**: If `totalRequests` is 0 and we divide by it, the program would crash or produce garbage results. Always check for zero before dividing!

#### Logging a request
```cpp
void Statistics::logRequest(string timestamp, string city,
                            string filename, string result, int edgeId)
{
    RequestLog log;              // Create a new log entry
    log.timestamp = timestamp;
    log.clientCity = city;
    log.filename = filename;
    log.result = result;
    log.edgeServerId = edgeId;
    requestLogs.push_back(log);  // Add it to the end of our vector
    // ↑ push_back() is like "append" in Python — adds to the end
}
```

#### Printing the statistics box
```cpp
void Statistics::print()
{
    cout << "  ╔══════════════════════════════════════╗" << endl;
    cout << "  ║         CDN STATISTICS REPORT        ║" << endl;
    cout << "  ╠══════════════════════════════════════╣" << endl;
    cout << "  ║  Total Requests : " << setw(8) << totalRequests << "           ║" << endl;
    //                                 ↑ setw(8) = set width to 8 characters
    //                                   This right-aligns numbers nicely
    cout << "  ║  Cache Hits     : " << setw(8) << hits << "  ✓        ║" << endl;
    cout << "  ║  Cache Misses   : " << setw(8) << misses << "  ✗        ║" << endl;
    cout << "  ║  Errors         : " << setw(8) << errors << "  !        ║" << endl;
    cout << "  ║  Hit Rate       : " << setw(7) << fixed << setprecision(1)
         << getHitRate() << "%           ║" << endl;
    //        ↑ fixed + setprecision(1) = show exactly 1 decimal place
    //          So 28.0% instead of 28% or 28.000%
    cout << "  ╚══════════════════════════════════════╝" << endl;
}
```

#### Printing the request log table
```cpp
void Statistics::printLog()
{
    if (requestLogs.empty())
    {
        cout << "  No requests logged yet." << endl;
        return;
    }

    // Print table header
    cout << "  " << string(78, '-') << endl;
    //               ↑ Creates a string of 78 dashes: "------..."
    cout << "  " << left << setw(22) << "Timestamp"
         << setw(14) << "City"
         << setw(20) << "File"
         << setw(10) << "Result"
         << setw(10) << "Edge ID" << endl;
    //   ↑ left = left-align text, setw() = column width

    cout << "  " << string(78, '-') << endl;

    // Print each log entry
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
}
```

#### Reset
```cpp
void Statistics::reset()
{
    totalRequests = 0;
    hits = 0;
    misses = 0;
    errors = 0;
    requestLogs.clear();   // Remove all log entries
    cout << "  Statistics reset." << endl;
}
```

---

### 1️⃣3️⃣ Utils.h — The Utilities Blueprint

📍 **File**: [Utils.h](file:///d:/CDN%20Simulator/Utils.h)
🎯 **Purpose**: Declares helper functions that aren't part of any class — things like printing the banner, simulating network delays, and getting the current time.

```cpp
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <thread>     // ← For sleep/delay functionality
#include <chrono>     // ← For time durations (milliseconds, seconds)
#include <ctime>      // ← For getting current date/time

using namespace std;

namespace Utils     // ← A namespace groups related functions together
{                   //    We call them as Utils::printBanner(), Utils::simulateLatency(), etc.

    void printBanner();                               // Show the ASCII art title
    void printSeparator(char ch = '=', int length = 60); // Print a line of characters
    void printMenu();                                 // Show the interactive menu
    void simulateLatency(int ms);                     // Pause for ms milliseconds
    string getCurrentTimestamp();                      // Get current date/time as string
    void printColored(string text, string color);     // Print colored text in terminal
}

#endif
```

> [!NOTE]
> **Why a `namespace` instead of a class?** These are standalone utility functions — they don't need to store any data. A namespace is perfect for grouping related functions without the overhead of creating objects. You can think of it as a "folder" for functions.

---

### 1️⃣4️⃣ Utils.cpp — The Utilities Logic

📍 **File**: [Utils.cpp](file:///d:/CDN%20Simulator/Utils.cpp)
🎯 **Purpose**: Implements all the utility functions.

#### Platform-specific includes
```cpp
#include "Utils.h"

#ifdef __MINGW32__       // ← Preprocessor check: "Are we using MinGW compiler?"
#include <windows.h>     //   If yes, include Windows API for the Sleep() function
#endif
```

> [!NOTE]
> **`#ifdef`** means "if defined". This is a **preprocessor directive** that checks at compile time whether a symbol exists. MinGW (a common C++ compiler on Windows) defines `__MINGW32__`, so we can detect it and use Windows-specific code.

#### printBanner() — ASCII art title
```cpp
void printBanner()
{
    // Prints a decorative box with "CDN" in large block letters
    // Uses Unicode box-drawing characters (╔, ═, ╗, ║, ╚, ╝)
    // and block characters (█, ╗, ╔, etc.) for the ASCII art
    cout << "  ╔═══════════════════════════════════╗" << endl;
    cout << "  ║     Content Delivery Network      ║" << endl;
    cout << "  ║     v1.0 | LRU Cache | Multi-Edge ║" << endl;
    cout << "  ╚═══════════════════════════════════╝" << endl;
    // ... (creates a visually appealing startup banner)
}
```

#### printSeparator() — Line divider
```cpp
void printSeparator(char ch, int length)
{
    cout << "  ";
    for (int i = 0; i < length; i++)
    {
        cout << ch;    // Print the character 'length' times
    }                  // Example: printSeparator('=', 5) → "  ====="
    cout << endl;
}
```

#### printMenu() — Interactive menu
```cpp
void printMenu()
{
    // Displays all 10 options:
    // [1] Request a File
    // [2] Add File to Origin Server
    // [3] View Edge Server Caches
    // [4] View Origin Server Files
    // [5] View Statistics & Request Log
    // [6] View Routing Table
    // [7] Run Batch Simulation
    // [8] Clear All Caches
    // [9] Reset Statistics
    // [0] Exit
}
```

#### simulateLatency() — Fake network delay
```cpp
void simulateLatency(int ms)
{
#ifdef __MINGW32__
    Sleep(ms);         // Windows/MinGW: use Windows API Sleep()
#else
    this_thread::sleep_for(chrono::milliseconds(ms));
    // ↑ Standard C++: pause the current thread for 'ms' milliseconds
    //   chrono::milliseconds(ms) creates a duration object
    //   this_thread::sleep_for() pauses execution for that duration
#endif
}
```

> [!TIP]
> **Why simulate latency?** In a real CDN, a cache hit might take 5ms but fetching from the origin server might take 100ms. By adding small delays, we make the simulation feel more realistic and educational.

#### getCurrentTimestamp() — Current date/time
```cpp
string getCurrentTimestamp()
{
    time_t now = time(0);              // Get current time as a number
    struct tm* timeinfo = localtime(&now); // Convert to human-readable format

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    // ↑ Format: "2026-07-20 21:04:51"
    //   %Y = year, %m = month, %d = day, %H = hour, %M = minute, %S = second

    return string(buffer);  // Convert char array to C++ string
}
```

#### printColored() — Colored terminal output
```cpp
void printColored(string text, string color)
{
    string colorCode = "";
    if (color == "red")         colorCode = "\033[31m";
    else if (color == "green")  colorCode = "\033[32m";
    else if (color == "yellow") colorCode = "\033[33m";
    // ... more colors

    string resetCode = "\033[0m";   // Reset to default color
    cout << colorCode << text << resetCode;
    // ↑ \033[31m is an "ANSI escape code" — a special sequence that
    //   tells the terminal to change text color.
    //   \033[0m resets back to normal.
}
```

> [!NOTE]
> **ANSI escape codes** are special character sequences that control terminal behavior (colors, cursor position, etc.). They start with `\033[` (the ESC character) followed by a code number. They work on most modern terminals (Windows Terminal, PowerShell, macOS Terminal, Linux).

---

### 1️⃣5️⃣ main.cpp — The Main Program

📍 **File**: [main.cpp](file:///d:/CDN%20Simulator/main.cpp)
🎯 **Purpose**: This is where everything comes together. It sets up the CDN, runs the interactive menu, and handles all user requests.

#### Includes and forward declarations
```cpp
#include <iostream>      // cout, cin
#include <fstream>       // File reading (for batch mode)
#include <sstream>       // String parsing (for batch mode)
#include <vector>        // Dynamic arrays
#include <map>           // Ordered map (for edge server lookup)

#include "OriginServer.h"
#include "EdgeServer.h"
#include "Router.h"
#include "Client.h"
#include "Statistics.h"
#include "Utils.h"

using namespace std;

// Forward declarations — tell the compiler these functions exist
// (their actual code is written below main())
void handleRequest(string city, string filename, OriginServer& origin,
                   map<int, EdgeServer*>& edges, Router& router, Statistics& stats);
void runBatchSimulation(OriginServer& origin, map<int, EdgeServer*>& edges,
                        Router& router, Statistics& stats);
```

> [!NOTE]
> **Forward declarations** let you use a function before writing its full code. The compiler just needs to know the function's name, parameters, and return type. The actual implementation can come later in the file.

#### Setup Phase (inside main())
```cpp
int main()
{
    // 1. Create the origin server and add 8 files
    OriginServer origin;
    origin.addFile("logo.png", "PNG image data - company logo 256x256px");
    origin.addFile("home.html", "<!DOCTYPE html>...");
    origin.addFile("video.mp4", "MP4 video stream data...");
    origin.addFile("style.css", "body { font-family: Arial; ... }");
    origin.addFile("app.js", "function init() { ... }");
    origin.addFile("data.json", "{ \"users\": 1500, ... }");
    origin.addFile("banner.jpg", "JPEG image data...");
    origin.addFile("api.php", "<?php echo json_encode(...); ?>");

    // 2. Create 3 edge servers in different regions
    EdgeServer edge1(1, "Mumbai", 5);     // ID=1, Region=Mumbai, Cache=5 files
    EdgeServer edge2(2, "Delhi", 5);      // ID=2, Region=Delhi, Cache=5 files
    EdgeServer edge3(3, "Bangalore", 5);  // ID=3, Region=Bangalore, Cache=5 files

    // 3. Store edge servers in a map for easy lookup by ID
    map<int, EdgeServer*> edges;
    edges[1] = &edge1;    // ← & = "address of" — stores a POINTER to edge1
    edges[2] = &edge2;    //   We use pointers so we work with the ORIGINAL objects
    edges[3] = &edge3;    //   (not copies of them)

    // 4. Configure the routing table
    Router router;
    router.addRoute("Mumbai", 1);       // Mumbai → Edge 1
    router.addRoute("Pune", 1);         // Pune → Edge 1 (closest)
    router.addRoute("Goa", 1);          // Goa → Edge 1 (closest)
    router.addRoute("Delhi", 2);        // Delhi → Edge 2
    router.addRoute("Jaipur", 2);       // Jaipur → Edge 2
    router.addRoute("Lucknow", 2);      // Lucknow → Edge 2
    router.addRoute("Bangalore", 3);    // Bangalore → Edge 3
    router.addRoute("Chennai", 3);      // Chennai → Edge 3
    router.addRoute("Hyderabad", 3);    // Hyderabad → Edge 3

    // 5. Initialize statistics tracker
    Statistics stats;
```

> [!IMPORTANT]
> **Pointers (`EdgeServer*`) and Address-of (`&`)**: We store **pointers** (memory addresses) to edge servers in the map, not copies. This is crucial because when we modify an edge server's cache through the pointer, the **original** edge server is modified. If we stored copies, changes wouldn't persist!

#### Interactive Menu Loop
```cpp
    int choice;
    bool running = true;

    while (running)          // ← Loop forever until user chooses to exit
    {
        Utils::printMenu();  // Show the menu
        cin >> choice;       // Read user's choice

        switch (choice)      // ← switch is like a chain of if/else if
        {
            case 1:  // Request a file
            {
                string city, filename;
                cout << "  Enter client city: ";
                cin >> city;
                cout << "  Enter filename: ";
                cin >> filename;
                handleRequest(city, filename, origin, edges, router, stats);
                break;
            }

            case 2:  // Add file to origin
            {
                string name, content;
                cout << "  Enter filename: ";
                cin >> name;
                cout << "  Enter content: ";
                cin.ignore();           // ← Clear the newline left by cin >>
                getline(cin, content);  // ← Read entire line (including spaces)
                origin.addFile(name, content);
                break;
            }

            case 3:  // View edge caches
                edge1.printCache();
                edge2.printCache();
                edge3.printCache();
                break;

            case 4:  // View origin files
                origin.printFiles();
                break;

            case 5:  // View statistics
                stats.print();
                stats.printLog();
                break;

            case 6:  // View routing table
                router.printRoutes();
                break;

            case 7:  // Run batch simulation
                runBatchSimulation(origin, edges, router, stats);
                break;

            case 8:  // Clear all caches
                edge1.clearCache();
                edge2.clearCache();
                edge3.clearCache();
                break;

            case 9:  // Reset statistics
                stats.reset();
                break;

            case 0:  // Exit
                stats.print();   // Show final statistics before exiting
                running = false; // This stops the while loop
                break;
        }
    }
    return 0;
}
```

> [!TIP]
> **`cin.ignore()`** is needed before `getline()` because `cin >>` leaves a newline character (`\n`) in the input buffer. If we don't clear it, `getline()` would read that leftover newline and think the user entered an empty string.

#### handleRequest() — The Core CDN Logic

This is the **most important function** in the entire program. It simulates what happens when a user requests a file:

```cpp
void handleRequest(string city, string filename, OriginServer& origin,
                   map<int, EdgeServer*>& edges, Router& router, Statistics& stats)
{
    string timestamp = Utils::getCurrentTimestamp();

    // ─── STEP 1: Find the nearest edge server ───
    int edgeId = router.getNearestEdge(city);

    if (edgeId == -1)   // No route found for this city
    {
        stats.addError();
        stats.logRequest(timestamp, city, filename, "ERROR", -1);
        return;         // ← Exit the function early
    }

    EdgeServer* edge = edges[edgeId];
    // ↑ Get a pointer to the edge server.
    //   edges[1] returns a pointer to edge1 (Mumbai)

    // ─── STEP 2: Check if the edge server has the file cached ───

    if (edge->hasFile(filename))
    {
        // ✅ CACHE HIT — file found on edge server!
        string content = edge->getFile(filename);
        Utils::simulateLatency(20);        // ~5ms delay (fast!)

        stats.addHit();
        stats.logRequest(timestamp, city, filename, "HIT", edgeId);
    }
    else
    {
        // ❌ CACHE MISS — file NOT on edge server

        // ─── STEP 3: Fetch from origin server ───
        Utils::simulateLatency(150);       // ~100ms delay (slow!)

        if (origin.hasFile(filename))
        {
            string content = origin.getFile(filename);

            // ─── STEP 4: Cache the file on the edge server ───
            edge->storeFile(filename, content);
            // ↑ Next time someone in this region requests this file,
            //   it will be a cache HIT!

            stats.addMiss();
            stats.logRequest(timestamp, city, filename, "MISS", edgeId);
        }
        else
        {
            // File doesn't exist anywhere!
            stats.addError();
            stats.logRequest(timestamp, city, filename, "ERROR", edgeId);
        }
    }
}
```

> [!IMPORTANT]
> **The `->` operator**: When you have a **pointer** to an object (like `EdgeServer* edge`), you use `->` instead of `.` to access its methods. So `edge->hasFile()` means "call hasFile() on the object that edge points to". It's equivalent to `(*edge).hasFile()`.

#### runBatchSimulation() — Process requests from a file

```cpp
void runBatchSimulation(OriginServer& origin, map<int, EdgeServer*>& edges,
                        Router& router, Statistics& stats)
{
    ifstream file("data/files.txt");   // Open the file for reading
    // ↑ ifstream = "input file stream" — a way to read files

    if (!file.is_open())   // Check if file opened successfully
    {
        cout << "ERROR: Could not open data/files.txt" << endl;
        return;
    }

    string line;
    int requestCount = 0;

    while (getline(file, line))         // Read one line at a time
    {
        if (line.empty() || line[0] == '#') continue;
        // ↑ Skip empty lines and comments (lines starting with #)
        //   "continue" skips to the next iteration of the while loop

        istringstream iss(line);        // Create a stream from the line
        // ↑ istringstream lets us parse a string like we'd parse user input
        //   It's like a virtual keyboard that "types" the string

        string city, filename;
        if (iss >> city >> filename)    // Extract city and filename
        {
            requestCount++;
            handleRequest(city, filename, origin, edges, router, stats);
        }
    }

    file.close();   // Always close files when done!
}
```

> [!TIP]
> **`istringstream`** is incredibly useful for parsing strings. It wraps a string and lets you use `>>` to extract words from it, just like you'd use `cin >>` to read from the keyboard. The line `"Mumbai logo.png"` gets split into `city = "Mumbai"` and `filename = "logo.png"`.

---

### 1️⃣6️⃣ data/files.txt — Batch Request Data

📍 **File**: [data/files.txt](file:///d:/CDN%20Simulator/data/files.txt)
🎯 **Purpose**: Contains pre-written requests that the batch simulation reads and processes.

```
# CDN Simulator Batch Request File
# Format: City Filename
# Lines starting with # are comments

Mumbai logo.png          ← Client in Mumbai requests logo.png
Delhi home.html          ← Client in Delhi requests home.html
Bangalore video.mp4      ← Client in Bangalore requests video.mp4
Mumbai home.html         ← Same city, different file
Delhi logo.png           ← Delhi needs logo.png too
Chennai style.css        ← Chennai routes to Edge 3 (Bangalore)
Hyderabad app.js         ← Hyderabad also routes to Edge 3
Mumbai logo.png          ← REPEAT! This should be a CACHE HIT ✅
... (25 total requests)
```

**Key observation**: When `Mumbai logo.png` appears the 2nd time, Edge Server 1 already has it cached from the first request. So it's a **cache hit** — no need to fetch from origin!

---

## 🔄 How a Request Flows Through the System

Let's trace what happens when a user in **Mumbai** requests **logo.png** for the **first time**:

```
Step 1: User selects "Request a File" from menu
        Types: city = "Mumbai", filename = "logo.png"

Step 2: handleRequest("Mumbai", "logo.png", ...) is called

Step 3: Router looks up "Mumbai" in its table
        → Found! Returns Edge Server ID = 1

Step 4: Edge Server 1 checks its cache
        → cache.contains("logo.png") returns FALSE (first time!)
        → CACHE MISS ❌

Step 5: Fetch from Origin Server
        → origin.hasFile("logo.png") returns TRUE
        → origin.getFile("logo.png") returns "PNG image data..."

Step 6: Store in Edge Server 1's cache
        → edge1.storeFile("logo.png", "PNG image data...")
        → cache.put("logo.png", "PNG image data...")
        → Now logo.png is cached on Edge 1!

Step 7: Statistics records a MISS
        → stats.addMiss()
        → stats.logRequest(..., "MISS", 1)
```

Now when **Mumbai requests logo.png again**:

```
Step 1-3: Same as before

Step 4: Edge Server 1 checks its cache
        → cache.contains("logo.png") returns TRUE ✅
        → CACHE HIT!

Step 5: Return from cache directly (no origin fetch needed!)
        → edge1.getFile("logo.png") returns "PNG image data..."
        → Much faster! (~5ms vs ~100ms)

Step 6: Statistics records a HIT
        → stats.addHit()
```

---

## 🛠 How to Build and Run

### Compile
```bash
g++ -std=c++17 -o cdn_sim.exe main.cpp Client.cpp Cache.cpp EdgeServer.cpp OriginServer.cpp Router.cpp Statistics.cpp Utils.cpp
```

**What each part means:**
| Part | Meaning |
|---|---|
| `g++` | The C++ compiler |
| `-std=c++17` | Use C++17 standard (needed for `auto`, `list`, etc.) |
| `-o cdn_sim.exe` | Name the output file "cdn_sim.exe" |
| `main.cpp Client.cpp ...` | All the source files to compile together |

### Run
```bash
.\cdn_sim.exe
```

---

## 📚 Glossary of C++ Concepts

| Concept | What it means | Where it's used |
|---|---|---|
| **Class** | A blueprint for creating objects with data and methods | Cache, Client, EdgeServer, etc. |
| **Object** | An instance of a class | `EdgeServer edge1(1, "Mumbai", 5);` |
| **Constructor** | Special method called when an object is created | `Cache(int size)` |
| **Include Guards** | `#ifndef/#define/#endif` — prevents double-including a header | Every `.h` file |
| **unordered_map** | A hash table: fast key→value lookups | `files`, `cityToEdge` |
| **list** | Doubly-linked list: fast insert/remove at any position | `accessOrder` in Cache |
| **vector** | Dynamic array that can grow | `requestLogs` in Statistics |
| **map** | Ordered key→value container | `edges` in main.cpp |
| **Pointer (`*`)** | A variable that stores a memory address | `EdgeServer* edge` |
| **Reference (`&`)** | An alias for another variable | `OriginServer& origin` |
| **`this->`** | Pointer to the current object | `this->city = city;` |
| **`->`** | Access member through a pointer | `edge->hasFile(filename)` |
| **Composition** | A class containing another class as a member | EdgeServer contains Cache |
| **Namespace** | A named scope to group related functions | `Utils::printBanner()` |
| **auto** | Let the compiler deduce the type | `for (auto& pair : files)` |
| **Initializer List** | Set member values before constructor body runs | `EdgeServer(...) : id(id), cache(cap)` |
| **Forward Declaration** | Tell compiler a function exists before defining it | `void handleRequest(...);` |
| **Preprocessor Directives** | `#ifdef`, `#ifndef` — compile-time checks | `#ifdef __MINGW32__` |
| **ANSI Escape Codes** | Special sequences for colored terminal output | `\033[32m` = green |
| **LRU** | Least Recently Used — eviction policy for caches | Cache class |
| **Sentinel Value** | A special value meaning "not found" | `-1` from `getNearestEdge()` |

---

> [!TIP]
> **Best way to learn from this project:**
> 1. Read this documentation alongside the actual code files
> 2. Run the simulator and try all 10 menu options
> 3. Run the batch simulation and observe which requests are HITs vs MISSes
> 4. Try modifying the cache capacity (change `5` to `3`) and see how eviction behavior changes
> 5. Add a new city and edge server to the system
