#include "Msg.hpp"

Msg::Msg(std::string message)
{
	std::string *temp_params;
	size_t pos_sep = 0, prev_sep = 0;
	int param_count = 0;

	if(message[0] == ':')
	{
		pos_sep = message.find(" ", prev_sep);
		_msg_prefix = message.substr(1, pos_sep);
		prev_sep = pos_sep;
	}
	else
		_msg_prefix = nullptr;
	pos_sep = message.find(" ", prev_sep);
	_msg_command = message.substr(prev_sep, pos_sep);
	_msg_params = nullptr;
	while ((pos_sep = message.find(" ", prev_sep)) > 0)
	{
		param_count++;
		temp_params = new std::string[param_count];
		for(int i = 0;i < param_count - 1; i++)
			temp_params[i] = _msg_command[i];
		temp_params[param_count - 1] = message.substr(prev_sep, pos_sep);
		if (_msg_params != nullptr)
			delete[] _msg_params;
		_msg_params = temp_params;
	}
}

Msg::~Msg()
{}