#include "Cache.h"

Cache::Cache(int size)
{
    capacity = size;
}

bool Cache::contains(string file)
{
    return files.find(file) != files.end();
}

string Cache::get(string file)
{
    if (!contains(file))
    {
        return "";
    }

    // LRU: Move accessed item to front (most recently used)
    accessOrder.erase(iteratorMap[file]);
    accessOrder.push_front(file);
    iteratorMap[file] = accessOrder.begin();

    return files[file];
}

void Cache::put(string file, string content)
{
    // If file already exists, update it and move to front
    if (contains(file))
    {
        files[file] = content;
        accessOrder.erase(iteratorMap[file]);
        accessOrder.push_front(file);
        iteratorMap[file] = accessOrder.begin();
        return;
    }

    // If cache is full, evict the least recently used item
    if ((int)files.size() >= capacity)
    {
        evict();
    }

    // Insert the new file
    files[file] = content;
    accessOrder.push_front(file);
    iteratorMap[file] = accessOrder.begin();
}

void Cache::evict()
{
    if (accessOrder.empty()) return;

    // Remove the least recently used item (back of the list)
    string lruFile = accessOrder.back();
    accessOrder.pop_back();
    files.erase(lruFile);
    iteratorMap.erase(lruFile);

    cout << "    [Cache] Evicted (LRU): " << lruFile << endl;
}

void Cache::clear()
{
    files.clear();
    accessOrder.clear();
    iteratorMap.clear();
}

int Cache::getSize()
{
    return (int)files.size();
}

int Cache::getCapacity()
{
    return capacity;
}

void Cache::printContents()
{
    if (files.empty())
    {
        cout << "    (empty)" << endl;
        return;
    }

    cout << "    Capacity: " << getSize() << "/" << capacity << endl;
    int index = 1;
    for (auto& file : accessOrder)
    {
        cout << "    " << index << ". " << file
             << " (" << files[file].length() << " bytes)"
             << (index == 1 ? " [Most Recent]" : "")
             << (index == (int)accessOrder.size() ? " [Least Recent]" : "")
             << endl;
        index++;
    }
}