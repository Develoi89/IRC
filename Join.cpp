#include "server.hpp"
#include "Channel.hpp"

std::vector<std::string> splitByComa(std::string str)
{
    std::vector<std::string> final;
    int start = 0, end = 0;

	while(start < str.size())
	{
		start = str.find_first_not_of(',', end);
		if(start == std::string::npos)
			break;
		end = str.find_first_of(',', start);
		if(end == std::string::npos)
		{
			final.push_back(str.substr(start));
			break;;
		}
		else
			final.push_back(str.substr(start, end - start));
	}
	return final;
}

int Server::cmdJoin(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    if(tokens.size() < 2)
    {
        std::cout << "not enought arguments." << std::endl;
        return 0;
    }
    std::vector<std::string> ch;
	std::vector<std::string> ps;

    ch = splitByComa(tokens[1]);
    if(tokens.size() > 2)
        ps = splitByComa(tokens[2]);

    int i = 0;
	//std::cout << ps.size() << std::endl;
    while(i < ch.size())
    {
        std::string key = ch[i];

        std::map<std::string, Channel>::iterator iter = _channels.find(key);
		
        if (iter != _channels.end())
		{
			// std::cout << "i: " << i << std::endl;
			// std::cout  <<"GET PASS: " <<  iter->second.getPass() << std::endl;
			// std::cout  <<"ITER PASS: " <<  iter->second.passSetted() << std::endl;

			if (i >= ps.size() && iter->second.passSetted())
				std::cout << ch[i] << " need a pass." << std::endl;
			else if(i >= ps.size() && !iter->second.passSetted()){
				iter->second.getClist().push_back(*aux);
				std::cout << "1Joined in " << key << " Channel." << std::endl;
			}
			else if (i <= ps.size() && ps[i] == iter->second.getPass() && iter->second.passSetted()){
            	iter->second.getClist().push_back(*aux);
				std::cout << "2Joined in " << key << " Channel." << std::endl;
			}
			else if (i <= ps.size() && !iter->second.passSetted()){
				iter->second.getClist().push_back(*aux);
				std::cout << "3Joined in " << key << " Channel." << std::endl;
			}
			else
				std::cout << "wrong pass." << std::endl;
		}
        else
        {
            Channel first(key, *aux);
			if (i < ps.size())
			{
				first.setPass(ps[i]);
				std::cout << first.getPass() << " as pass setted for " << key << " channel." << std::endl;
			}
			_channels[key] = first;
			std::cout << "Crerated " << key << " channel." << std::endl;
        }
        i++;
    }

    return 0;
}