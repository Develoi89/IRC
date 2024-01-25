#include "Comands.hpp"

int cmdKick() //Eject a client from the channel
{
    std::cout << "KICK called" << std::endl;
    return 0;
}
int cmdInvite() //Invite a client to a channel
{
    std::cout << "INVITE called" << std::endl;
    return 0;
}
int cmdTopic() //Change or view the channel topic
{
    std::cout << "TOPIC called" << std::endl;
    return 0;
}
int cmdMode() //Change the channel’s mode:
{
    std::cout << "MODE called" << std::endl;
    return 0;
}

bool checkCmd(Client *aux, std::vector<std::string> tokens)
{
    std::map<std::string, int(*)()> functionMap;

    functionMap["KICK"] = &cmdKick;
    functionMap["INVITE"] = &cmdInvite;
    functionMap["TOPIC"] = &cmdTopic;
    functionMap["MODE"] = &cmdMode;

    std::string key = tokens[0];

    std::map<std::string, int (*)()>::iterator iter = functionMap.find(key);
    if (iter != functionMap.end()) 
    {
        iter->second(); 
    } 
    else
    {
        std::cerr << "Función no encontrada" << std::endl;
    }
    return true;
}