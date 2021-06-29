#ifndef IRCC_COMMAND_BONUS_HPP
#define IRCC_COMMAND_BONUS_HPP

#include "Server.hpp"
#define FAIL "-1"
#define SUCCESS "0"

class IRCServer;

class Command
{
    private:
        Command();
        static std::string makeString(std::string *params, int index);
        static void makeError(std::string, std::string, std::string, int, IRCServer *);
        static void makeSucces(std::string, std::string, int, IRCServer *, int);
        static void makeAuthResponse(int, IRCServer *);

    public:
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
        static void cmd_upload(int fd, std::string *params, IRCServer *server);
        static void cmd_download(int fd, std::string *params, IRCServer *server);
};

#endif //IRCC_COMMAND_HPP
