#include "Channel.hpp"

Channel::Channel()
{}

Channel::Channel(const std::string &channelName) : _channel_name(channelName)
{}

Channel::~Channel()
{
	_clients.clear();
}

void Channel::AddClient(int fd)
{_clients.insert(fd);}

void Channel::RemoveClient(int fd)
{_clients.erase(fd);}