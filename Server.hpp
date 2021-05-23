#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "define_error.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>

#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

class msg;
class client;
class channel;

class Server
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

	/// users_list ??
	/*
	std::string const _serv_target_host_addr; //  accepts CIDR format
	std::string const _serv_password;
	std::string const _serv_target_host_name;
	std::string const _serv_target_port;
	std::string const _serv_target_class;
	std::string const _serv_target_flags;
	*/

////	socket?????? ///
	fd_set _master_set;
	fd_set _servers_set;							//// connected servers fds
	fd_set _clients_set;							//// connected clients fds
	int		_fd_max;

	std::vector<msg*> _msg_list;					//// message queue on this server (vector)

	std::vector<client*> _client_active_list;		//// active clients on this server (vector)

	std::vector<channel*> _channel_active_list;		//// active channels on this server (vector)


	typedef struct _serv_s_channel					//// channel struct
	{
		std::string _channel_name;
		std::string _channel_type;
		struct _serv_s_channel* next;
	}				_serv_t_channel;
	std::vector<_serv_s_channel*> _server_channel_list;

	typedef struct _serv_s_list						//// server list
	{
		std::string _list_name;
		int			_server_fd;
		struct _serv_s_list* next;
	}				_serv_t_list;
	std::vector<_serv_s_list*> _serv_server_list;

	typedef struct _serv_s_client					//// client list
	{
		std::string _client_name;
		std::vector<std::string> _last_client_name;
		std::string _client_pass;
		std::string _client_host;
		std::string _client_nik_name;
		std::string _client_status;
		std::string _client_flag;
		int 		_client_fd;
		struct _serv_s_client* next;
	}				_serv_t_client;
	std::vector<_serv_s_client*> _serv_client_list;

public:
	Server();
	Server(std::string file); /// create new server with config file;
	~Server();
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
