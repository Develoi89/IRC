#include "Client.hpp"


Client::Client(int fd){
    _pw = false;
    _fd = fd;
    _name ="";
    _buff = "";
    _user = "";
    _nickname = "";
}

Client::Client(const Client &c): _pw(c._pw), _fd(c._fd), _name(c._name), _buff(c._buff), _user(c._user), _nickname(c._nickname){} 

