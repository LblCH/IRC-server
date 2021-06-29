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
    Client *client = server->getClient(fd);
    if (!params[0].empty())
    {
        if (params[0][0] == '#')
        {
            server->addChannel(params[0], fd);
            client->addChanel(server->getChannel(params[0]));
        } else
            makeError("476", params[0], "Invalid channel name", fd, server);
    } else
        makeError("461", "JOIN", "Not enough parameters.", fd, server);
}

void Command::cmd_user(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (params != nullptr && !params[0].empty() && !params[1].empty() && !params[2].empty()
    && !params[3].empty())
    {
        client->setHostName(params[0]);
        std::string str = makeString(params, 3);
        client->setRealName(str);
        if (!client->getName().empty() && (server->getServPass() == client->getPass() || server->getServPass().empty()))
            makeAuthResponse(fd, server);
    } else
        makeError("461", "USER", "Not enough parameters.", fd, server);
}

void Command::cmd_kill(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (params != nullptr && !params[0].empty() && !params[1].empty())
    {
        if (client->getOperator() == 1)
        {
            Client *delete_client = server->getClientByName(params[0]);
            if (delete_client != nullptr)
            {
                std::string str = makeString(params, 1);
                makeSucces("KILL", str, delete_client->getfd(), server, fd);
                server->deleteClient(fd);
                close(delete_client->getfd());
                FD_CLR(delete_client->getfd(), &server->_master_set);
            } else
                makeError("401", params[0], "No such nick", fd, server);
        }
    } else
        makeError("461", "KILL", "Not enough parameters.", fd, server);
}

void Command::cmd_nick(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (client != nullptr && params != nullptr && !params[0].empty())
    {
        Client *check = server->getClientByName(params[0]);
        if (check == nullptr) {
            client->setName(params[0]);
            if (!client->getRealName().empty() && (server->getServPass() == client->getPass() || server->getServPass().empty()))
                makeAuthResponse(fd, server);
        }
        else
            makeError("433", params[0], "Nickname is already in use.", fd, server);
    }
}

void Command::cmd_notice(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (params != nullptr && client != nullptr && !params[0].empty())
    {
        if (params[0][0] == '#')
        {
            Channel *channel = server->getChannel(params[0]);
            if (channel != nullptr)
            {
                std::string str = makeString(params, 1);
                channel->sendPrivMessage(fd, "NOTICE", str);
            }
        } else
        {
            Client *other_client = server->getClientByName(params[0]);
            if (other_client != nullptr)
            {
                std::string str = makeString(params, 1);
                makeSucces("NOTICE", str, other_client->getfd(), server, fd);
            }
        }
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
	Client *client = server->getClient(fd);
	if (params != nullptr)
    {
        if (client->getRealName().empty())
            makeError("462", "\b", "You may not reregister", fd, server);
        if (params[0] != server->getServPass())
            makeError("464", "\b", "Pass not correct", fd, server);
        else {
            client->setPass(params[0]);
            if (!client->getName().empty())
                makeAuthResponse(fd, server);
        }
    } else
        makeError("461", "PASS", "Not enough parameters.", fd, server);
}

void Command::cmd_privmsg(int fd, std::string *params, IRCServer *server) {
    Client *client = server->getClient(fd);
    if (params != nullptr && client != nullptr && !params[0].empty() && !params[1].empty())
    {
        if (params[0][0] == '#')
        {
            Channel *channel = server->getChannel(params[0]);
            if (channel != nullptr)
            {
                std::string str = makeString(params, 1);
                channel->sendPrivMessage(fd, "PRIVMSG", str);
            } else
                makeError("403", params[0], "No such channel", fd, server);
        } else
        {
            Client *other_client = server->getClientByName(params[0]);
            if (other_client != nullptr)
            {
                std::string str = makeString(params, 1);
                makeSucces("PRIVMSG", str, other_client->getfd(), server, fd);
            } else
                makeError("401", params[0], "No such nick", fd, server);
        }
    } else
        makeError("461", "PRIVMSG", "Not enough parameters.", fd, server);
}

std::string Command::makeString(std::string *params, int index) {
    std::string response;
    params += index;
    while (params->c_str()[0] != '\0')
    {
        response.append(params->begin(), params->end());
        if ((params + 1)->c_str()[0] != '\0')
            response.append(" ");
        params++;
    }
    return (response);
}

void Command::makeError(std::string s1, std::string s2, std::string s3, int fd, IRCServer *server) {
    std::string err = ":alcogolics@russia.ru ";
    err.append(s1);
    err.append(" ");
    std::string nick = server->getClient(fd)->getName();
    err.append(nick.empty() ? "*" : nick);
    err.append(" ");
    err.append(s2);
    err.append(" :");
    err.append(s3);
    err.append("\r\n");
    send(fd, err.c_str(), err.length(), 0);
}

void Command::makeSucces(std::string s1, std::string s2, int fd, IRCServer *server, int my_fd) {
    std::string message = ":";
    Client *my = server->getClient(my_fd);
    message.append(my->getName());
    message.append("!");
    message.append(my->getHostName());
    message.append("@127.0.0.1 ");
    message.append(s1);
    message.append(" ");
    message.append(server->getClient(fd)->getName());
    message.append(" ");
    message.append(s2);
    message.append("\r\n");
    send(fd, message.c_str(), message.length(), 0);
}

void Command::makeAuthResponse(int fd, IRCServer *server) {
    std::string temp;
    Client *my = server->getClient(fd);
    temp = "Welcome to the Russian IRC Network";
    temp.append(my->getName());
    temp.append("!");
    temp.append(my->getHostName());
    temp.append("@127.0.0.1 ");
    makeError("001", "\b", temp, fd, server);
    makeError("002", "\b", "Your host is alcogolics@russia.ru, running version InspIRCd-3", fd, server);
    makeError("003", "\b", "This server was created 17:13:16 Jun 29 2021", fd, server);
    makeError("004", "\b", "alcogolics@russia.ru InspIRCd-3 iosw biklmnopstv :bklov", fd, server);
    makeError("005", "AWAYLEN=200 CASEMAPPING=ascii CHANLIMIT=#:20 CHANMODES=b,k,l,imnpst CHANNELLEN=64 CHANTYPES=# ELIST=CMNTU HOSTLEN=64 KEYLEN=32 KICKLEN=255 LINELEN=512 MAXLIST=b:100", "are supported by this server", fd, server);
    makeError("005", "MAXTARGETS=20 MODES=20 NAMELEN=128 NETWORK=Russia NICKLEN=30 PREFIX=(ov)@+ SAFELIST STATUSMSG=@+ TOPICLEN=307 USERLEN=10 USERMODES=,,s,iow WHOX", "are supported by this server", fd, server);
}

//Command &Command::operator=(const Command &rhs)
//{
//}