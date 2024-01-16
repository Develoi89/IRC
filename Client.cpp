#include "Client.hpp"


Client::Client(int fd){
    pw = false;
    this->fd = fd;
    this->name ="";
    this->buff = "";
    this->user = "";
    this->nickname = "";
}

Client::Client(const Client &c): pw(c.pw), fd(c.fd), name(c.name), buff(c.buff), user(c.user), nickname(c.nickname){} 

