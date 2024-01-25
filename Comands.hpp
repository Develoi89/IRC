#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Client.hpp"

bool checkCmd(Client *aux, std::vector<std::string> tokens);

int cmdKick(); //Eject a client from the channel
int cmdInvite(); //Invite a client to a channel
int cmdTopic(); //Change or view the channel topic
int cmdMode(); //Change the channel’s mode:

#endif