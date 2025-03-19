#include <iostream>

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
    else
    {
        std::cout << "Unknown argument" << std::endl;
        printHelp();
        return 0;
    }
    
    return 0;
}
