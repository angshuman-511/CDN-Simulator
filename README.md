# 📖 CDN Simulator — Complete Documentation

> **Audience**: Beginners learning C++. This document explains **every single file** in the project, line by line, so you understand not just *what* the code does, but *why* it does it.

---

## 📑 Table of Contents

1. [What is a CDN?](#-what-is-a-cdn)
2. [Project Overview](#-project-overview)
3. [How the Files are Organized](#-how-the-files-are-organized)
4. [Architecture Diagram](#-architecture-diagram)
5. [How a Request Flows Through the System](#-how-a-request-flows-through-the-system)
6. [How to Build and Run](#-how-to-build-and-run)
7. [Glossary of C++ Concepts](#-glossary-of-c-concepts)

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
