#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{}

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

