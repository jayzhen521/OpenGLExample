#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <iostream>
#include <fstream>

#include "Util.h"

bool ReadFile(const char* pFileName, std::string& outFile)
{
    std::ifstream f(pFileName);

    bool ret = false;

    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        ret = true;
    }
    else {
        std::cerr << "read " << pFileName << " error." << std::endl;
    }

    return ret;
}

long long GetCurrentTimeMillis()
{
#ifdef WIN32    
    return GetTickCount64();
#else
    timeval t;
    gettimeofday(&t, NULL);

    long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
    return ret;
#endif    
}
