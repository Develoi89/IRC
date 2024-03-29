#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "Client.hpp"

class Client;

class Channel
{
	private:
		std::vector<std::string> _msgs;
		std::vector<Client> _clist;
		std::string _name;
		std::string _pass;
		std::string _topic;
		std::string _status;

		std::set<int> _ops;
		std::set<int> _members;
		std::set<int> _inviteds;
		std::map<char, bool> _mode;
		int limit;
		bool	_passsetted;
		
	public:
		Channel(){}
		Channel(std::string name, Client op);

		void setMsgs(std::string msg);
		void setPass(std::string pass);

		std::string getPass(){return _pass;}
		bool passSetted(){return _passsetted;}
		std::string getName(){return _name;}
		std::string getTopic(){return _topic;}
		void setTopic(std::string s){this->_topic = s;}
		std::vector<Client> &getClist();
		bool isMember(int searchNumber)const;
		bool isOps(int searchNumber)const;
		bool isInvited(int searchNumber)const;
		void setLimit(int lim){limit = lim;}
		int getLimit(){return limit;}
		void exMode(char s, char c);

		void deleteMem(int fd);
		void deleteOp(int fd);
		void deleteInv(int fd);
		void deleteClient(int fd);

		std::set<int> getOps(){return _ops;}
		std::set<int> getMem(){return _members;}
		std::set<int> getInv(){return _inviteds;}

		bool getMode(char m){return _mode[m];}

		void setOps(int fd);
		void remOps(int fd);
		void setMem(int fd);
		void setInv(int fd);

		std::vector<std::string> &getMsgs();
};

#endif