#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <vector>
#include "Client.hpp"

class Client;

bool    isNum(std::string str);
bool    verifyPort(std::string port);
std::vector<std::string> tkparser(std::string str, std::string nt);
void registerMsg(Client &c);

#endif