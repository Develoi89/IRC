#ifndef CLIENT_HPP
# define CLIENT_HPP
#include "server.hpp"

class Client{
    private:
        bool pw;
        bool rg;

        int fd;
        std::string buff;
        std::string user;
        std::string name;
        std::string nickname;
    public:
        Client(int fd);
        Client(const Client &c);
        Client & operator =(const Client &client);


        void    setNick(std::string s) {this->nickname = s;}
        void    setName(std::string s) {this->name = s;}
        void    setUser(std::string s)  {this->user = s;}
        void    setBuffer(std::string s)  {this->buff = s;}
        void    setPw(bool s)  {this->pw = s;}
        void    setRg(bool s)  {this->rg = s;}


        const std::string &getNick() const {return this->nickname;}
        const std::string &getName() const {return this->name;}
        const std::string &getUser() const {return this->user;}
        const std::string &getBuffer() const {return this->buff;}
        const int &getFd() const {return this->fd;}
        const bool &getPw() const {return this->pw;}
        const bool &getRg() const {return this->rg;}
        void newMessage(std::string str);

};

#endif