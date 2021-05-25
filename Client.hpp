#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "Server.hpp"

class Client
{
private:
	std::string const _name;
	std::string _host_name;
	std::string _pass;
	std::string _buf;
	int 		_fd;
public:
	Client(int fd);
	int getfd();
	// change pass
	// connect to serv
	// disconnect from serv
	// send msg
	// post msg ???
	// change nik_name
	// change type
	// connect channel // create channel
	// leave channel

};

class Server : public Client
{
private:
	int hopcount;

};

#endif //FT_IRC_CLIENT_H