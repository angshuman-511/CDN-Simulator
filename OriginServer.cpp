#include "OriginServer.h"

void OriginServer::addFile(string name, string content)
{
    files[name] = content;
}

bool OriginServer::hasFile(string name)
{
    return files.find(name) != files.end();
}

string OriginServer::getFile(string name)
{
    return files[name];
}

int OriginServer::getFileCount()
{
    return (int)files.size();
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
    for (auto& pair : files)
    {
        cout << "    " << index << ". " << pair.first
             << " (" << pair.second.length() << " bytes)" << endl;
        index++;
    }
}