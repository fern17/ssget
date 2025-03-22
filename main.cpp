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
    std::cout << "\tfetch products: fetch the list of all products" << std::endl;
    std::cout << "\tfetch supported_products: fetch the list of all currently supported products" << std::endl;
}

bool getValue(JsonParser &jsonParser, const std::string &key, std::string &outputString)
{
    std::string value;
    bool result = jsonParser.get<std::string>(key, value);
    if (result)
    {
        outputString += key + " " + value + "\n";
    }
    return result;
}

bool getProducts(JsonParser &jsonParser, bool supportedOnly, std::string &outputString)
{
    std::list<std::string> products;
    bool result = jsonParser.getProducts(supportedOnly, products);
    if (result)
    {
        outputString.clear();
        outputString += std::string(supportedOnly ? "Supported products:" : "Products:") + "\n";
        for (auto prod : products)
        {
            outputString += "- " + prod + "\n";
        }
    }
    return result;
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
            std::string outputString;
            bool result = false;
            if (key == "products")
            {
                result = getProducts(jsonParser, false, outputString);
            }
            else if (key == "supported_products")
            {
                result = getProducts(jsonParser, true, outputString);
            }
            else
            {
                result = getValue(jsonParser, key, outputString);
            }
            
            if (result)
            {
                std::cout << outputString << std::endl;
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
