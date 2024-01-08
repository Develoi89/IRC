#include "Login.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        std::cout << "not enought arguments" << std::endl;
        return 0;
    }
    Login start(argv[2]);
    start.verifyPort(argv[1]);
    return 0;
}