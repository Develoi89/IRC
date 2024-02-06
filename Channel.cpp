#include "Channel.hpp"

Channel::Channel(std::string name, Client op)
{
    //_topic = "hola mundo.";
    _name = name;
    _clist.push_back(op);
    _passsetted = false;
    _status = "\"@\", 0x40";
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

void Channel::setOps(int fd)
{
    _ops.insert(fd);
}

void Channel::setMem(int fd)
{
    _members.insert(fd);
}

void Channel::setInv(int fd)
{
    _inviteds.insert(fd);
}
