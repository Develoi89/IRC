#include "Comands.hpp"

int cmdKick(Client *aux, std::vector<std::string> tokens) //Eject a client from the channel
{
    std::cout << "KICK called" << std::endl;
    return 0;
}

int cmdInvite(Client *aux, std::vector<std::string> tokens) //Invite a client to a channel
{
    std::cout << "INVITE called" << std::endl;
    return 0;
}

int cmdTopic(Client *aux, std::vector<std::string> tokens) //Change or view the channel topic
{
    std::cout << "TOPIC called" << std::endl;
    return 0;
}

int cmdMode(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    std::cout << "MODE called" << std::endl;
    return 0;
}

int cmdJoin(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    std::cout << "JOIN called" << std::endl;
    return 0;
}

int cmdPong(Client *aux, std::string tk)
{
    aux->newMessage("PONG irc.telo.net " + tk);
}

int cmdPing(Client *aux, std::vector<std::string> tokens)
{
    cmdPong(aux, tokens[1]);
    return 0;
}


bool Comands::checkCmd(Client *aux, std::vector<std::string> tokens)
{
    std::map<std::string, int(*)(Client*, std::string)> functionMap;

    functionMap["KICK"] = &cmdKick;
    functionMap["INVITE"] = &cmdInvite;
    functionMap["TOPIC"] = &cmdTopic;
    functionMap["MODE"] = &cmdMode;
    functionMap["JOIN"] = &cmdJoin;
    functionMap["PING"] = &cmdPing;

    std::string key = tokens[0];

    std::map<std::string, int (*)(Client*, std::string)>::iterator iter = functionMap.find(key);
    if (iter != functionMap.end()) 
    {
        iter->second(aux, tokens); 
    } 
    else
    {
        std::cerr << "Función no encontrada" << std::endl;
    }
    return true;
}