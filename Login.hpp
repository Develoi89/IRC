#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <iostream>

class Login
{
    private:
        std::string _pass;
        Login();
    public:
        Login(std::string pas);
        ~Login();
        bool    verifyPort(std::string port);
};


#endif