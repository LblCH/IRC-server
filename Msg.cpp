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
		std::cout << _msg_prefix << std::endl;
		prev_sep = pos_sep + 1;
	}
	if ((message.substr(pos_sep, message.size() - pos_sep)).size() > 0)
	{
		pos_sep = message.find(" ", prev_sep);
		_msg_command = message.substr(prev_sep, pos_sep);
		_msg_params = nullptr;
		while ((pos_sep = message.find(" ", prev_sep)) != std::string::npos)
		{
			param_count++;
			temp_params = new std::string[param_count];
			for (int i = 0; i < param_count - 1; i++)
				temp_params[i] = _msg_command[i];
			temp_params[param_count - 1] = message.substr(prev_sep, pos_sep);
			std::cout <<  temp_params[param_count - 1].size() << std::endl;
			if (_msg_params != nullptr)
				delete[] _msg_params;
			_msg_params = temp_params;
			prev_sep = pos_sep + 1;
		}
		param_count = (param_count > 0) ? param_count + 1 : 0;
		temp_params = new std::string[param_count];
		for (int i = 0; i < param_count - 1; i++)
			temp_params[i] = _msg_command[i];
		temp_params[param_count - 1] = message.substr(prev_sep);
		if (_msg_params != nullptr)
			delete[] _msg_params;
		_msg_params = temp_params;
	}
}

Msg::~Msg()
{
	if (_msg_params != nullptr)
		delete[] _msg_params;
}

std::string *Msg::get_params()
{
	return _msg_params;
}

std::string Msg::get_prefix()
{
	return _msg_prefix;
}