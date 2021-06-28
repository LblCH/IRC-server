#include "Command.hpp"

Command::Command()
{}

Command::~Command()
{
}

Command::Command(const Command &copy)
{
}

void Command::cmd_join(int fd, std::string *params, IRCServer *server) {
    printf("HELLO!");
}

void Command::cmd_user(int fd, std::string *params, IRCServer *server) {
    return;
}

void Command::cmd_kill(int fd, std::string *params, IRCServer *server) {

}

void Command::cmd_nick(int fd, std::string *params, IRCServer *server) {

}

void Command::cmd_notice(int fd, std::string *params, IRCServer *server) {

}

void Command::cmd_oper(int fd, std::string *params, IRCServer *server) {

}

void Command::cmd_pass(int fd, std::string *params, IRCServer *server) {

}

void Command::cmd_privmsg(int fd, std::string *params, IRCServer *server) {

}

//Command &Command::operator=(const Command &rhs)
//{
//}