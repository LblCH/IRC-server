#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "Server.hpp"

class Channel;

class Client
{
    private:
        int 		_fd;
        int         _operator;
        std::string _name;
        std::string _host_name;
        std::string _real_name;
        std::string _pass;
        std::map<std::string , Channel *> _channel_list;

    public:
        Client(int fd);
        ~Client();
        int getOperator() const;
        void addChanel(Channel *);
        void leaveChannels();
        const std::string &getRealName() const;
        const std::map<std::string, Channel *> &getChannelList() const;
        int getfd();
        void setHostName(const std::string &hostName);
        void setRealName(const std::string &realName);
        void setPass(const std::string &pass);
        void setOperator(int oper);
        const std::string &getHostName() const;
        void setName(const std::string &name);
        const std::string &getName() const;
};

#endif //FT_IRC_CLIENT_H