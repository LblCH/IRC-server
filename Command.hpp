#ifndef IRCC_COMMAND_HPP
#define IRCC_COMMAND_HPP

#include "Server.hpp"

class IRCServer;

class Command
{
private:
	Command();

public:
//	Command();
	virtual ~Command();
	Command(const Command &);
	Command &operator=(const Command &rhs);
    static void cmd_kill(int fd, std::string *params, IRCServer *server);
    static void cmd_join(int fd, std::string *params, IRCServer *server);
    static void cmd_nick(int fd, std::string *params, IRCServer *server);
    static void cmd_notice(int fd, std::string *params, IRCServer *server);
    static void cmd_oper(int fd, std::string *params, IRCServer *server);
    static void cmd_pass(int fd, std::string *params, IRCServer *server);
    static void cmd_privmsg(int fd, std::string *params, IRCServer *server);
    static void cmd_user(int fd, std::string *params, IRCServer *server);
};

#endif //IRCC_COMMAND_HPP
