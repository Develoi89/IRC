#include "Channel.hpp"

Channel::Channel(std::string name, Client op): _name(name)
{
    _ops.push_back(op);
}

void Channel::setMsgs(std::string msg)
{
    _msgs.push_back(msg);
}

std::vector<std::string>  &Channel::getMsgs()
{
    return _msgs;
}
