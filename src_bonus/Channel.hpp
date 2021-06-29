#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP

#include "Server.hpp"

class IRCServer;

class Channel
{
    private:
        Channel();
        std::string const _channel_name;
        std::set<int> _clients;
        IRCServer *_server;
        void sendServerMessage(int fd);
    public:
        explicit Channel(const std::string &channelName, int fd, IRCServer *);
        virtual ~Channel();
        void sendMessage(int fd, std::string s1, std::string s2);
        void AddClient(int fd);
        void RemoveClient(int fd);
        void sendPrivMessage(int fd, std::string s1, std::string s2);
        const std::string &getChannelName() const;
};


#endif //FT_IRC_CHANNEL_HPP
