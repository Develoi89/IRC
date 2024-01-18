#include "server.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        std::cout << "not enought arguments" << std::endl;
        return 0;
    }
    Server server(std::stoi(argv[1]), argv[2]);
    if(!server.verifyPort(argv[1])){
        return 0;
    }
    server.loop();
    return 0;
}