#include "Client.hpp"


Client::Client(int fd)
{
    pw = false;
    rg = false;
    this->fd = fd;
    this->name ="";
    this->buff = "";
    this->user = "";
    this->nickname = "";
}

Client::Client(const Client &c): pw(c.pw), rg(c.rg), fd(c.fd), name(c.name), buff(c.buff), user(c.user), nickname(c.nickname){} 

void Client::newMessage(std::string str)
{
    std::string message = str + "\r\n";
    send(this->fd, message.c_str(), message.size(), 0);
}

Client & Client::operator=(const Client &client)
{
    this->pw = client.pw;
    this->rg = client.rg;
    this->fd = client.fd;
    this->name =client.name;
    this->buff = client.buff;
    this->user = client.user;
    this->nickname = client.nickname;
    return *this;
}

