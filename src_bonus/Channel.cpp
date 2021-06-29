#include "Channel.hpp"

Channel::Channel()
{}

Channel::Channel(const std::string &channelName, int fd, IRCServer *server) : _channel_name(channelName)
{
    _clients.insert(fd);
    _server = server;
    sendMessage(fd, "JOIN", _channel_name);
    sendServerMessage(fd);
}

Channel::~Channel()
{
	_clients.clear();
}

void Channel::AddClient(int fd)
{
    _clients.insert(fd);
    sendMessage(fd, "JOIN", _channel_name);
    sendServerMessage(fd);
}

void Channel::RemoveClient(int fd)
{_clients.erase(fd);}

void Channel::sendMessage(int fd, std::string s1, std::string s2) {
    std::string message = ":";
    message.append(_server->getClient(fd)->getName());
    message.append("!");
    message.append(_server->getClient(fd)->getHostName());
    message.append("@127.0.0.1 ");
    message.append(s1);
    message.append(" :");
    message.append(s2);
    message.append("\r\n");
    std::set<int>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        send(*it, message.c_str(), message.length(), 0);
        it++;
    }
}

void Channel::sendServerMessage(int fd) {
    std::string message = ":alcogolics@russia.ru 353 ";
    message.append(_server->getClient(fd)->getName());
    message.append(" = ");
    message.append(_channel_name);
    message.append(" :");
    std::set<int>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        message.append(_server->getClient(*it)->getName());
        message.append(" ");
        it++;
    }
    message.append("\r\n");
    message.append(":alcogolics@russia.ru 366 ");
    message.append(_server->getClient(fd)->getName());
    message.append(" ");
    message.append(_channel_name);
    message.append(" :End of /NAMES list.\r\n");
    send(fd, message.c_str(), message.length(), 0);
}

void Channel::sendPrivMessage(int fd, std::string s1, std::string s2) {
    std::string message = ":";
    Client *my = _server->getClient(fd);
    message.append(my->getName());
    message.append("!");
    message.append(my->getHostName());
    message.append("@127.0.0.1 ");
    message.append(s1);
    message.append(" ");
    message.append(_channel_name);
    message.append(" ");
    message.append(s2);
    message.append("\r\n");
    std::set<int>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if (*it != fd)
            send(*it, message.c_str(), message.length(), 0);
        it++;
    }
}

const std::string &Channel::getChannelName() const {
    return _channel_name;
}
