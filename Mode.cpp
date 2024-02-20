#include "server.hpp"

int Server::cmdMode(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    if(tokens.size() < 2)
    {
        aux->newMessage("461 " + aux->getNick() + " MODE :Not enought arguments.");
        return 0;
    }
	else if (findChannelByName(tokens[1]) == 0)
	{
		aux->newMessage(std::string("403 ") +  aux->getNick() + " " + tokens[1] + " :No such channel");
        return 0;
	}
    else if (tokens[2].size() == 2 && tokens.size() > 2)
    {
        switch (tokens[2][1])
        {
        case 'i':
            /* Set/remove Invite-only channel */
            break;
        case 't':
            /* Set/remove the restrictions of the TOPIC command to channel operators */
            break;
        case 'k':
            /* Set/remove the channel key (password) */
            break;
        case 'o':
            /* Give/take channel operator privilege */
            break;
        case 'l':
            /* Set/remove the user limit to channel */
            break;
        default:
            /* code */
            break;
        }
    }

}