#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{
    _operator = 0;
}

Client::~Client()
{
    delete this;
}

int Client::getfd()
{
	return _fd;
}

void Client::setName(const std::string &name) {
    _name = name;
}

const std::string &Client::getName() const {
    return _name;
}

void Client::setHostName(const std::string &hostName) {
    _host_name = hostName;
}

void Client::setRealName(const std::string &realName) {
    _real_name = realName;
}

void Client::setFlags(const std::string &flags) {
    _flags = flags;
}

void Client::setPass(const std::string &pass) {
    _pass = pass;
}

int Client::getOperator() const {
    return _operator;
}

void Client::setOperator(int oper) {
    _operator = oper;
}

const std::string &Client::getRealName() const
{
	return _real_name;
}
