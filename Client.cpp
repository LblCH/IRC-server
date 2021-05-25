#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{}

int Client::getfd()
{
	return _fd;
}