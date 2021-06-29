#include <sstream>
#include "Msg.hpp"

	//message = комманда только до \r\n (не включительно)
Msg::Msg(const std::string& message)
{
    if (!message.empty()) {
        std::vector<std::string> array;
        std::istringstream ss(message);
        std::string param;
        while (ss >> param)
            array.push_back(param);
        _msg_command = array[0];
        _msg_params = nullptr;
        if (array.size() > 1) {
            _msg_params = new std::string[array.size()];
            for (int i = 1; i < array.size(); i++)
                _msg_params[i - 1] = array[i];
            _msg_params[array.size() - 1] = "";
        }
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

const std::string &Msg::getMsgCommand() const {
    return _msg_command;
}
