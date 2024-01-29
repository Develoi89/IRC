#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Client.hpp"

class Comands
{
    private:

        Comands();
        ~Comands();

    public:

        static bool checkCmd(Client *aux, std::vector<std::string> tokens);
};
#endif