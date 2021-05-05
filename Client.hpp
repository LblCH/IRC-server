#include <iostream>


#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H


class Client
{
private:
	std::string const _cli_name;
	std::string _cli_nik_name;
	std::string _cli_pass;
	std::string _cli_type;
	std::string _cli_host_name;
	std::string status;
public:
	// create new client
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


#endif //FT_IRC_CLIENT_H
