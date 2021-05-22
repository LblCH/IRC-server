#include <iostream>


#ifndef FT_IRC_MSG_HPP
#define FT_IRC_MSG_HPP


class Msg
{
private:
	std::string const _msg_prefix;
	std::string const _msg_command;
	std::string const *_msg_params;
public:
	Msg(std::string message);
	~Msg();
};


#endif //FT_IRC_MSG_HPP
