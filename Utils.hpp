#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <vector>

bool    isNum(std::string str);
bool    verifyPort(std::string port);
std::vector<std::string> tkparser(std::string str, std::string nt);

#endif