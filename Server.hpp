#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>
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

class Client;
class Msg;

class IRCServer
{
private:
	std::string _serv_host_name;
	std::string _serv_ip_serv;
	std::string _geographic_location; // 	RU = 643 // ISO-3166-1 // https://ru.wikipedia.org/wiki/ISO_3166-1
	std::string _serv_Port;
	std::string _serv_SIDl;
	//// admin information
	std::string _serv_admin_location_info;
	std::string _serv_admin_email;
	std::string _serv_admin_other_inform;
	std::string _serv_network_name;
	std::string _serv_directory;
	int			_listener_fd;
	int			_key;

////	socket?????? ///
	fd_set _master_set;
	fd_set _servers_set;							//// connected servers fds
	fd_set _users_set;
	fd_set _services_set;							//// connected clients fds
	int		_fd_max;

	std::vector<Msg> _msg_list;					//// message queue on this server (vector)

	std::vector<Channel*> _channel_active_list;		//// active channels on this server (vector)

	std::map<int, std::string> _client_buffer_in;
	std::map<int, std::string> _client_buffer_out;

	std::map<int, Client> _client_list;

	std::vector<Channel> _server_channel_list;

	void _processing_msg(std::string);

public:
	IRCServer();
	IRCServer(std::string file); /// create new server with config file;
	~IRCServer();
	void announce();  /// show server fields
	void start();
	void work();
	void stop();
	// post msg;
	// add channel

	// check network;
	// add client
	// check client
	// ???
};


#endif //FT_IRC_SERVER_HPP
