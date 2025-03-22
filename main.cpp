#include <iostream>
#include <cstring>
#include <sstream>
#include "WebDownloader.h"
#include "JsonParser.h"

constexpr std::string_view url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

void printHelp()
{
    std::cout << "ssget" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\tfetch [key]: fetch key from the json file" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printHelp();
        return 0;
    }
    else if (strcmp(argv[1], "help") == 0)
    {
        printHelp();
        return 0;
    }
    else if (strcmp(argv[1], "fetch") == 0)
    {
        if (argc < 3)
        {
            std::cout << "Missing key to fetch" << std::endl;
            return 1;
        }
        
        WebDownloader webDownloader(url.data());
        std::string webContents;
        bool result = webDownloader.fetchContents(webContents);
        if (result)
        { 
            JsonParser jsonParser(webContents);
            std::string key(argv[2]);
            std::string value;
            bool result = jsonParser.get<std::string>(key, value);
            if (result)
            {
                std::cout << key << " " << value << std::endl;
                return 0;
            }
            else
            {
                std::cout << "Invalid key" << std::endl;
                return 1;
            }
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
