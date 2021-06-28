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
    Client *client = server->getClient(fd);
    if (params->length() == 4)
    {
        client->setHostName(params[0]);
        client->setFlags(params[1]);
        client->setRealName(params[3]);
    }
}

void Command::cmd_kill(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (client->getOperator() == 1 && params[0].length() == 2)
    {
        if (!params[0].empty())
        {
            Client *delete_client = server->getClientByName(params[0]);
            if (delete_client != nullptr)
            {
                send(delete_client->getfd(), params[1].c_str(), params[1].length(), 0);
                close(delete_client->getfd());
                FD_CLR(delete_client->getfd(), &server->_master_set);
            }
        }
    }
}

void Command::cmd_nick(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (client != nullptr && params != nullptr && !params[0].empty())
        client->setName(params[0]);
}

void Command::cmd_notice(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (client != nullptr && params->length() == 2)
    {
        Client *other_client = server->getClientByName(params[0]);
        if (other_client != nullptr)
            send(other_client->getfd(), params[1].c_str(), params[1].length(), 0);
    }
}

void Command::cmd_oper(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (client->getOperator() == 1 && params[0].length() == 2)
    {
        if (!params[0].empty())
        {
            Client *other_client = server->getClientByName(params[0]);
            if (other_client != nullptr)
                other_client->setOperator(1);
        }
    }
}

void Command::cmd_pass(int fd, std::string *params, IRCServer *server) {

}

void Command::cmd_privmsg(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (client != nullptr && !params[0].empty())
    {
        Client *other_client = server->getClientByName(params[0]);
        if (other_client != nullptr)
            send(other_client->getfd(), params[1].c_str(), params[1].length(), 0);
    }
    //TO_DO errors
}

//Command &Command::operator=(const Command &rhs)
//{
//}