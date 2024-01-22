#include <iostream>

bool    isNum(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if(str[i] > '9' || str[i] < '0')
            return false;
    }
    return true;
}

bool    verifyPort(std::string port)
{
    int num;

    if (!isNum(port))
    {
        std::cout << "Error: Port should be numeric." << std::endl;
        return false;
    }

    num = std::stoi(port);
    if(num > 65535 || num < 1)
    {
        std::cout << "Error: invalid range of Port." << std::endl;
        return false;
    }
    std::cout << "port verifyed " << port << std::endl;
    return true;
}
