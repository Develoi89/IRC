#include "Client.hpp"


Client::Client(int fd){
    this->fd = fd;
    this->name ="";
    this->buff = "";
    this->user = "";
    this->nickname = "";
}

