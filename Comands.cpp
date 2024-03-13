#include "server.hpp"

typedef int (Server::*CmdFuncPtr)(Client*, std::vector<std::string>);

bool Server::checkCmd(Client *aux, std::vector<std::string> tokens)
{
    std::map<std::string, CmdFuncPtr> functionMap;

    functionMap["KICK"] = &Server::cmdKick;
    functionMap["INVITE"] = &Server::cmdInvite;
    functionMap["TOPIC"] = &Server::cmdTopic;
    functionMap["MODE"] = &Server::cmdMode;
    functionMap["JOIN"] = &Server::cmdJoin;
    functionMap["PING"] = &Server::cmdPing;
    functionMap["PRIVMSG"] = &Server::cmdPrivmsg;

    std::string key = tokens[0];

    std::map<std::string, CmdFuncPtr>::iterator iter = functionMap.find(key);
    if (iter != functionMap.end()) 
    {
        (this->*(iter->second))(aux, tokens); 
    } 
    return true;
}