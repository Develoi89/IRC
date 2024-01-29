#include <iostream>
#include <vector>
#include "Utils.hpp"
#include "server.hpp"

void registerMsg(Client &c)
{
    c.newMessage(" :Welcome to the irc.telo.net Network, " + c.getNick() + "!"+ c.getUser() + "@127.0.0.1");
    c.newMessage(" :Your host is irc.telo.net, running version 1.0");
    c.newMessage("irc.telo.net 1.0 itkol");
}

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

std::vector<std::string> tkparser(std::string str, std::string nt)
{
    std::vector<std::string> final;
    int start = 0, end = 0;

	while(start < str.size())
	{
		start = str.find_first_not_of(nt, end);
		if(start == std::string::npos)
			break;
		end = str.find_first_of(nt, start);
		if(end == std::string::npos)
		{
			final.push_back(str.substr(start));
			break;;
		}
		else
			final.push_back(str.substr(start, end - start));
	}
	return final;	
}
