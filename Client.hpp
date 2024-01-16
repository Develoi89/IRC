#ifndef CLIENT_HPP
# define CLIENT_HPP
#include "server.hpp"
class Client{
    private:
        int fd;
        std::string buff;
        std::string user;
        std::string name;
        std::string nickname;
    public:
        Client(int fd);

        void    setNick(std::string s) {this->nickname = s;}
        void    setName(std::string s) {this->name = s;}
        void    setUser(std::string s)  {this->user = s;}
        void    setBuffer(std::string s)  {this->buff = s;}

        const std::string &getNick() const {return this->nickname;}
        const std::string &getName() const {return this->name;}
        const std::string &getUser() const {return this->user;}
        const std::string &getBuffer() const {return this->buff;}
};

#endif