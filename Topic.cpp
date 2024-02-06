#include "server.hpp"

// int Server::findChannelByName(std::string name){
//     std::map<std::string, Channel>::iterator it = _channels.find(name);

//     if (it != _channels.end()) {
//         return 1;
//     } else {
//         std::cout << "Canal no encontrado." << std::endl;
//     }
//     return 0;
// }


int Server::cmdTopic(Client *aux, std::vector<std::string> tokens) //Change or view the channel topic
{
    //  if(tokens.size() < 2){
    //     aux->newMessage(std::string("461 ") + aux->getNick() + tokens[0] + ":Not enough parameters");
    //     return ;
    // }

    // //no existe el channel
    // //no tiene permisos
    // //creacion del topic
    // if(ch->getTopic() != ""){
	// 	aux->newMessage(std::string("332 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic());
	// 	std::cout << std::string("332 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic() << std::endl;
	// 	aux->newMessage(std::string("333 ") + aux->getNick() + " " + ch->getName() + " " + aux->getNick() + " " + _currentTime());
	// 	std::cout << std::string("333 ") + aux->getNick() + " " + ch->getName() + " " + aux->getNick() + " " + _currentTime() << std::endl;
	// }else{
	// 	aux->newMessage(std::string("331 ") + aux->getNick() + " " + ch->getName() + " :No topic is set");
	// }
    return 0;

}