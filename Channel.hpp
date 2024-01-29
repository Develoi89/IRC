#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include <vector>
#include "Client.hpp"

class Channel
{
	private:
		std::vector<std::string> _msgs;
		std::vector<Client> _ops;
		std::string _name;

	public:
		Channel(){}
		Channel(std::string name, Client op);

		void setMsgs(std::string msg);

		std::vector<std::string> &getMsgs();
};

#endif