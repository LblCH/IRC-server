#include "Server.hpp"

void init_cmds(IRCServer *server)
{
    server->_cmds["KILL"] = Command::cmd_kill;
    server->_cmds["NICK"] = Command::cmd_nick;
	server->_cmds["JOIN"] = Command::cmd_join;
    server->_cmds["NOTICE"] = Command::cmd_notice;
    server->_cmds["OPER"] = Command::cmd_oper;
    server->_cmds["PASS"] = Command::cmd_pass;
    server->_cmds["PRIVMSG"] = Command::cmd_privmsg;
    server->_cmds["USER"] = Command::cmd_user;
	server->_cmds["UPLOAD"] = Command::cmd_upload;
	server->_cmds["DOWNLOAD"] = Command::cmd_download;
}