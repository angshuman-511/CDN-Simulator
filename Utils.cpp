#include "Utils.h"

#ifdef __MINGW32__
#include <windows.h>
#endif

namespace Utils
{
    void printBanner()
    {
        cout << endl;
        cout << "  ╔═══════════════════════════════════════════════════════╗" << endl;
        cout << "  ║                                                       ║" << endl;
        cout << "  ║          ██████╗██████╗ ███╗   ██╗                    ║" << endl;
        cout << "  ║         ██╔════╝██╔══██╗████╗  ██║                    ║" << endl;
        cout << "  ║         ██║     ██║  ██║██╔██╗ ██║                    ║" << endl;
        cout << "  ║         ██║     ██║  ██║██║╚██╗██║                    ║" << endl;
        cout << "  ║         ╚██████╗██████╔╝██║ ╚████║                    ║" << endl;
        cout << "  ║          ╚═════╝╚═════╝ ╚═╝  ╚═══╝                   ║" << endl;
        cout << "  ║                                                       ║" << endl;
        cout << "  ║         Content Delivery Network Simulator            ║" << endl;
        cout << "  ║         v1.0 | LRU Cache | Multi-Edge                 ║" << endl;
        cout << "  ║                                                       ║" << endl;
        cout << "  ╚═══════════════════════════════════════════════════════╝" << endl;
        cout << endl;
    }

    void printSeparator(char ch, int length)
    {
        cout << "  ";
        for (int i = 0; i < length; i++)
        {
            cout << ch;
        }
        cout << endl;
    }

    void printMenu()
    {
        cout << endl;
        printSeparator('=', 50);
        cout << "  CDN SIMULATOR MENU" << endl;
        printSeparator('=', 50);
        cout << "  [1]  Request a File" << endl;
        cout << "  [2]  Add File to Origin Server" << endl;
        cout << "  [3]  View Edge Server Caches" << endl;
        cout << "  [4]  View Origin Server Files" << endl;
        cout << "  [5]  View Statistics & Request Log" << endl;
        cout << "  [6]  View Routing Table" << endl;
        cout << "  [7]  Run Batch Simulation (data/files.txt)" << endl;
        cout << "  [8]  Clear All Caches" << endl;
        cout << "  [9]  Reset Statistics" << endl;
        cout << "  [0]  Exit" << endl;
        printSeparator('-', 50);
        cout << "  Enter choice: ";
    }

    void simulateLatency(int ms)
    {
#ifdef __MINGW32__
        Sleep(ms);
#else
        this_thread::sleep_for(chrono::milliseconds(ms));
#endif
    }

    string getCurrentTimestamp()
    {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);

        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }

    void printColored(string text, string color)
    {
        // ANSI color codes for terminal
        string colorCode = "";
        if (color == "red")         colorCode = "\033[31m";
        else if (color == "green")  colorCode = "\033[32m";
        else if (color == "yellow") colorCode = "\033[33m";
        else if (color == "blue")   colorCode = "\033[34m";
        else if (color == "cyan")   colorCode = "\033[36m";
        else if (color == "white")  colorCode = "\033[37m";

        string resetCode = "\033[0m";
        cout << colorCode << text << resetCode;
    }
}
