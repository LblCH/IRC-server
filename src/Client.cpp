#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{
    _operator = 0;
    _pass = "";
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

int Client::getOperator() const {
    return _operator;
}

void Client::setOperator(int oper) {
    _operator = oper;
}

const std::string &Client::getHostName() const {
    return _host_name;
}

const std::string &Client::getRealName() const
{
	return _real_name;
}

const std::map<std::string, Channel *> &Client::getChannelList() const
{
	return _channel_list;
}

void Client::setPass(const std::string &pass)
{
	_pass = pass;
}

void Client::addChanel(Channel *channel) {
    _channel_list[channel->getChannelName()] = channel;
}

void Client::leaveChannels() {
    std::map<std::string , Channel *>::iterator it = _channel_list.begin();
    while (it != _channel_list.end())
    {
        Channel *channel = it->second;
        channel->RemoveClient(_fd);
        channel->sendMessage(_fd, "LEAVE", channel->getChannelName());
        it++;
    }
}

const std::string &Client::getPass() const {
    return _pass;
}
