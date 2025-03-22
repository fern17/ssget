#include <iostream>
#include <cstring>
#include <sstream>
#include "WebDownloader.h"
#include "SimplestreamsInterpreter.h"

constexpr std::string_view url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

void printHelp()
{
    std::cout << "ssget" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\tfetch [key]: fetch key from the json file" << std::endl;
    std::cout << "\tfetch products: fetch the list of all products" << std::endl;
    std::cout << "\tfetch supported_products: fetch the list of all currently supported products" << std::endl;
    std::cout << "\tfetch current_lts: fetch the current LTS version" << std::endl;
    std::cout << "\tfetch sha256 [version] [arch] [date]: fetch the SHA256 of the disk image for the given version" << std::endl;
}

bool getValue(SimplestreamsInterpreter &simplestreamsInterpreter, const std::string &key, std::string &outputString)
{
    std::string value;
    bool result = simplestreamsInterpreter.getStringValue(key, value);
    if (result)
    {
        outputString += key + " " + value + "\n";
    }
    return result;
}

bool getProducts(SimplestreamsInterpreter &simplestreamsInterpreter, bool supportedOnly, std::string &outputString)
{
    std::list<std::string> products;
    bool result = simplestreamsInterpreter.getProducts(supportedOnly, products);
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

bool getCurrentLTSVersion(SimplestreamsInterpreter &simplestreamsInterpreter, std::string &outputString)
{
    std::string version;
    bool result = simplestreamsInterpreter.getCurrentLTSVersion(version);
    if (result)
    {
        outputString += "Latest LTS version: " + version + "\n";
    }
    return result;
}

bool getDiskImageSHA256(SimplestreamsInterpreter &simplestreamsInterpreter,
                        const std::string &version,
                        const std::string &arch,
                        const std::string &date,
                        std::string &outputString)
{
    std::string sha256Value;
    bool result = simplestreamsInterpreter.getImageDiskSHA256(version, arch, date, sha256Value);
    if (result)
    {
        outputString += "SHA256: " + sha256Value;
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
            SimplestreamsInterpreter simplestreamsInterpreter(webContents);
            std::string key(argv[2]);
            std::string outputString;
            bool result = false;
            if (key == "products")
            {
                result = getProducts(simplestreamsInterpreter, false, outputString);
            }
            else if (key == "supported_products")
            {
                result = getProducts(simplestreamsInterpreter, true, outputString);
            }
            else if (key == "current_lts")
            {
                result = getCurrentLTSVersion(simplestreamsInterpreter, outputString);
            }
            else if (key == "sha256")
            {
                if (argc < 6)
                {
                    std::cout << "One or more arguments are missing in order to fetch sha256" << std::endl;
                    return 1;
                }
                std::string version(argv[3]);
                std::string arch(argv[4]);
                std::string date(argv[5]);
                result = getDiskImageSHA256(simplestreamsInterpreter, version, arch, date, outputString);
;            }
            else
            {
                result = getValue(simplestreamsInterpreter, key, outputString);
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
