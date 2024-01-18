#ifndef CLIENT_HPP
# define CLIENT_HPP
#include "server.hpp"

class Client{
    private:
        bool _pw;
        int _fd;
        std::string _buff;
        std::string _user;
        std::string _name;
        std::string _nickname;

    public:
        Client(int fd);
        Client(const Client &c);

        void    setNick(std::string s) {_nickname = s;}
        void    setName(std::string s) {_name = s;}
        void    setUser(std::string s)  {_user = s;}
        void    setBuffer(std::string s)  {_buff = s;}
        void    setPw(bool s)  {_pw = s;}

        const std::string &getNick() const {return _nickname;}
        const std::string &getName() const {return _name;}
        const std::string &getUser() const {return _user;}
        const std::string &getBuffer() const {return _buff;}

        const bool &getPw() const {return _pw;}
};

#endif