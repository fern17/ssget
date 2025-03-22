#include <iostream>
#include <cstring>
#include <sstream>
#include "WebDownloader.h"

constexpr std::string_view url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

void printHelp()
{
    std::cout << "ssget" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printHelp();
        return 0;
    }
    if (strcmp(argv[1], "ping") == 0)
    {
        std::cout << "pong" << std::endl;
        return 0;
    }
    else if (strcmp(argv[1], "pong") == 0)
    {
        std::cout << "ping" << std::endl;
        return 0;
    }
    else if (strcmp(argv[1], "help") == 0)
    {
        printHelp();
        return 0;
    }
    else if (strcmp(argv[1], "fetch") == 0)
    {
        WebDownloader webDownloader(url.data());
        std::string contents;
        bool result = webDownloader.fetchContents(contents);
        if (result)
        { 
            std::cout << contents << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Failed to fetch contents from " << url << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Unknown argument" << std::endl;
        printHelp();
        return 0;
    }
    
    return 0;
}
