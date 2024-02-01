#include "Channel.hpp"

Channel::Channel(std::string name, Client op)
{
    _name = name;
    _clist.push_back(op);
    _passsetted = false;
}

void Channel::setPass(std::string pass)
{
    _pass = pass;
    _passsetted = true;
}

void Channel::setMsgs(std::string msg)
{
    _msgs.push_back(msg);
}

std::vector<std::string>  &Channel::getMsgs()
{
    return _msgs;
}

std::vector<Client> &Channel::getClist()
{
    return _clist;
}