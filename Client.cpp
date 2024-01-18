#include "Client.hpp"


Client::Client(int fd){
    _pw = false;
    _rg = false;
    _fd = fd;
    _name ="";
    _buff = "";
    _user = "";
    _nickname = "";
}

Client::Client(const Client &c): pw(c.pw), rg(c.rg), fd(c.fd), name(c.name), buff(c.buff), user(c.user), nickname(c.nickname){} 

void Client::newMessage(std::string str){
    std::string message = str + "\r\n";
    send(_fd, message.c_str(), message.size(), 0);
}
