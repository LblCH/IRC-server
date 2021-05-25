//
// Created by Adeline Vivien on 4/25/21.
//

#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{}

int Client::getfd()
{
	return _fd;
}