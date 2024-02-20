#include "Channel.hpp"

void Channel::deleteClient(int fd)
{
    std::vector<Client>::iterator iter;
    for (iter = _clist.begin(); iter != _clist.end(); iter++)
        if(iter->getFd() == fd)
        {
            _clist.erase(iter);
            break;
        }
}

void Channel::deleteMem(int fd)
{
    _members.erase(fd);
}
void Channel::deleteOp(int fd)
{
    _ops.erase(fd);
}
void Channel::deleteInv(int fd)
{
    _inviteds.erase(fd);
}

Channel::Channel(std::string name, Client op)
{
    //_topic = "hola mundo.";
    _name = name;
    _clist.push_back(op);
    _passsetted = false;
    _status = "\"@\", 0x40";
    _mode['i'] = false;
    _mode['t'] = false;
    _mode['k'] = false;
    _mode['o'] = false;
    _mode['l'] = false;
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

bool Channel::isMember(int searchNumber) const 
{
    std::set<int>::const_iterator it = _members.find(searchNumber);
    return it != _members.end();
}

bool Channel::isOps(int searchNumber) const 
{
    std::set<int>::const_iterator it = _ops.find(searchNumber);
    return it != _ops.end();
}

bool Channel::isInvited(int searchNumber)const
{
    std::set<int>::const_iterator it = _inviteds.find(searchNumber);
    return it != _inviteds.end();
}

