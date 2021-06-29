#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "define_error.h"
#include "define_common.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "Client.hpp"
#include "Msg.hpp"
#include "Channel.hpp"
#include "Command.hpp"

class Client;
class Channel;
class Msg;

class IRCServer
{
    private:
        IRCServer();
        typedef std::map<std::string, void (*)(int, std::string *, IRCServer *)> t_cmdmap;
        std::string _serv_host_name;
        std::string _serv_ip_serv;
        std::string _geographic_location;                   // 	RU = 643 // ISO-3166-1 // https://ru.wikipedia.org/wiki/ISO_3166-1
        std::string _serv_Port;
        std::string _serv_SIDl;
        std::string _serv_admin_location_info;
        std::string _serv_admin_email;
        std::string _serv_admin_other_inform;
        std::string _serv_network_name;
        std::string _serv_directory;
        std::string _serv_pass;
        int			_listener_fd;
        fd_set      _servers_set;						    // connected servers fds
        fd_set      _users_set;                             // connected clients fds
        int         _fd_max;
        int         _key;

        std::map<std::string, Channel*> _channel_list;      // active channels on this server
        std::map<int, std::string> _client_buffer_in;
        std::map<int, std::string> _client_buffer_out;

        std::map<int, Client*> _client_list;                // active users on this server
        void _processing_msg(std::string, int fd, int nbytes);

    public:
        fd_set _master_set;
        t_cmdmap	_cmds;

        IRCServer(const std::string& file, int, char**);    // create new server with config file;
        virtual ~IRCServer();
        void announce();                                    // show server fields
        void start();
        void work();
        const std::string &getServPass() const;
        void addChannel(std::string name, int fd);
        Client *getClient(int fd);
        Channel *getChannel(std::string name);
        Client *getClientByName(const std::string& name);
};

void init_cmds(IRCServer *);

#endif //FT_IRC_SERVER_HPP
