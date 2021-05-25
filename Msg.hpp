#ifndef FT_IRC_MSG_HPP
#define FT_IRC_MSG_HPP

#include <iostream>
#include "Server.hpp"

class Msg
{
private:
	std::string _msg_prefix;
	std::string _msg_command;
	std::string *_msg_params;
public:
	Msg(std::string message);
	~Msg();
	std::string *get_params();
	std::string get_prefix();
};


#endif //FT_IRC_MSG_HPP
