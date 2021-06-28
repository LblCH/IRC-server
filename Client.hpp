#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "Server.hpp"

class Client
{
private:
	std::string _name;
	std::string _host_name;
	std::string _real_name;
	std::string _flags;
	std::string _pass;
	int 		_fd;
	int         _operator;
public:
    int getOperator() const;

	const std::string &getRealName() const;

public:
	Client(int fd);
	~Client();
	int getfd();

    void setHostName(const std::string &hostName);

    void setRealName(const std::string &realName);

    void setFlags(const std::string &flags);

    void setPass(const std::string &pass);

    void setOperator(int oper);

    void setName(const std::string &name);

    const std::string &getName() const;
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