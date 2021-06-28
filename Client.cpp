#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{}

Client::~Client()
{}

int Client::getfd()
{
	return _fd;
}

Client::~Client()
{

};
