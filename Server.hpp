#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "define_error.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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
	int _count_all_server;
	//// admin information
	std::string _serv_admin_location_info;
	std::string _serv_admin_email;
	std::string _serv_admin_other_inform;
	std::string _serv_network_name;

	int			_serv_port; // client blocks the default 6667.
	std::string _serv_directory;
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

	std::vector<msg*> _msg_list;					//// message queue on this server (vector)

	std::vector<client*> _client_active_list;		//// active clients on this server (vector)

	std::vector<channel*> _channel_active_list;		//// active channels on this server (vector)


	typedef struct _serv_s_channel					//// channel struct
	{
		std::string _serv_channel_name;
		std::string _serv_channel_type;
		struct _serv_s_channel* next;
	}				_serv_t_channel;
	std::vector<_serv_s_channel*> _server_channel_list;

	typedef struct _serv_s_list						//// server list
	{
		std::string _serv_list_name;
		struct _serv_s_list* next;
	}				_serv_t_list;
	std::vector<_serv_s_list*> _serv_server_list;

	typedef struct _serv_s_client					//// client list
	{
		std::string _serv_client_name;
		std::vector<std::string> _last_client_name;
		std::string _serv_client_pass;
		std::string _serv_client_host;
		std::string _serv_client_nik_name;
		std::string _serv_client_status;
		std::string _serv_client_flag;
		struct _serv_s_client* next;
	}				_serv_t_client;
	std::vector<_serv_s_client*> _serv_client_list;

public:
	Server();
	Server(std::string file); /// create new server with config file;
	~Server();
	void announce();  /// show server fields
	void start();
	void stop();
	// post msg;
	// add channel

	// check network;
	// add client
	// check client
	// ???
};


#endif //FT_IRC_SERVER_HPP
