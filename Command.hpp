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
};

void cmd_admin(int fd, std::string *params, IRCServer *server);
void cmd_away(int fd, std::string *params, IRCServer *server);
void cmd_connect(int fd, std::string *params, IRCServer *server);
void cmd_die(int fd, std::string *params, IRCServer *server);
void cmd_error(int fd, std::string *params, IRCServer *server);
void cmd_info(int fd, std::string *params, IRCServer *server);
void cmd_invite(int fd, std::string *params, IRCServer *server);
void cmd_ison(int fd, std::string *params, IRCServer *server);
void cmd_join(int fd, std::string *params, IRCServer *server);
void cmd_kick(int fd, std::string *params, IRCServer *server);
void cmd_kill(int fd, std::string *params, IRCServer *server);
void cmd_links(int fd, std::string *params, IRCServer *server);
void cmd_list(int fd, std::string *params, IRCServer *server);
void cmd_lusers(int fd, std::string *params, IRCServer *server);
void cmd_mode(int fd, std::string *params, IRCServer *server);
void cmd_motd(int fd, std::string *params, IRCServer *server);
void cmd_msg(int fd, std::string *params, IRCServer *server);
void cmd_names(int fd, std::string *params, IRCServer *server);
void cmd_nick(int fd, std::string *params, IRCServer *server);
void cmd_notice(int fd, std::string *params, IRCServer *server);
void cmd_oper(int fd, std::string *params, IRCServer *server);
void cmd_part(int fd, std::string *params, IRCServer *server);
void cmd_pass(int fd, std::string *params, IRCServer *server);
void cmd_ping(int fd, std::string *params, IRCServer *server);
void cmd_pong(int fd, std::string *params, IRCServer *server);
void cmd_privmsg(int fd, std::string *params, IRCServer *server);
void cmd_query(int fd, std::string *params, IRCServer *server);
void cmd_quit(int fd, std::string *params, IRCServer *server);
void cmd_rehash(int fd, std::string *params, IRCServer *server);
void cmd_restart(int fd, std::string *params, IRCServer *server);
void cmd_service(int fd, std::string *params, IRCServer *server);
void cmd_servlist(int fd, std::string *params, IRCServer *server);
void cmd_server(int fd, std::string *params, IRCServer *server);
void cmd_squery(int fd, std::string *params, IRCServer *server);
void cmd_squit(int fd, std::string *params, IRCServer *server);
void cmd_stats(int fd, std::string *params, IRCServer *server);
void cmd_summon(int fd, std::string *params, IRCServer *server);
void cmd_time(int fd, std::string *params, IRCServer *server);
void cmd_topic(int fd, std::string *params, IRCServer *server);
void cmd_trace(int fd, std::string *params, IRCServer *server);
void cmd_user(int fd, std::string *params, IRCServer *server);
void cmd_userhost(int fd, std::string *params, IRCServer *server);
void cmd_users(int fd, std::string *params, IRCServer *server);
void cmd_version(int fd, std::string *params, IRCServer *server);
void cmd_wallops(int fd, std::string *params, IRCServer *server);
void cmd_who(int fd, std::string *params, IRCServer *server);
void cmd_whois(int fd, std::string *params, IRCServer *server);
void cmd_whowas(int fd, std::string *params, IRCServer *server);

#endif //IRCC_COMMAND_HPP
