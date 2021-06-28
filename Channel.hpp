#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP

#include "Server.hpp"

class Channel
{
private:
	Channel();
	std::string const _channel_name;
	std::set<int> _clients;
public:
	explicit Channel(const std::string &channelName);
	virtual ~Channel();
	void AddClient(int fd);
	void RemoveClient(int fd);
};


#endif //FT_IRC_CHANNEL_HPP
