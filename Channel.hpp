#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include <vector>
#include "Client.hpp"

class Client;

class Channel
{
	private:
		std::vector<std::string> _msgs;
		std::vector<Client> _clist;
		std::string _name;
		std::string _pass;
		bool	_passsetted;
		
	public:
		Channel(){}
		Channel(std::string name, Client op);

		void setMsgs(std::string msg);
		void setPass(std::string pass);

		std::string getPass(){return _pass;}
		bool passSetted(){return _passsetted;}

		std::vector<Client> &getClist();

		std::vector<std::string> &getMsgs();
};

#endif