#include "Server.hpp"

IRCServer::IRCServer(int argc, char** argv)
{
	if (argc == 3)
	{
		_serv_Port = argv[1];
		_serv_pass = argv[2];
	}
	else
		printf("Usage: ./ircserv <port> <password>");
	_serv_host_name = "s";
	_serv_ip_serv = "127.0.0.1";
	_geographic_location = "101";
	_serv_SIDl = "101";
	_serv_admin_location_info = "RF";
	_serv_admin_email = "admin@admin.ru";
	_serv_admin_other_inform = "other_info";
	_serv_network_name = "Russia";
	_serv_directory = "./";
}

IRCServer::IRCServer() {
}

IRCServer::~IRCServer()
{
	std::cout << "Destruct serv" << std::endl;
}

void IRCServer::announce()
{
	std::cout << "Start anonce" << std::endl;
	std::cout << "serv_host_name : "  << _serv_host_name  << std::endl;
	std::cout << "serv_ip_serv serv : " << _serv_ip_serv  << std::endl;
	std::cout << "geographic_location serv : " << _geographic_location  << std::endl;
	std::cout << "serv_Port serv : " << _serv_Port  << std::endl;
	std::cout << "serv_SIDl serv : "<<  _serv_SIDl  << std::endl;
	std::cout << "serv_admin_location_info serv : " << _serv_admin_location_info  << std::endl;
	std::cout << "serv_admin_email serv : " << _serv_admin_email  << std::endl;
	std::cout << "serv_admin_other_inform serv : "<<  _serv_admin_other_inform  << std::endl;
	std::cout << "serv_network_name serv : " << _serv_network_name  << std::endl;
	std::cout << "serv_directory serv : " << _serv_directory  << std::endl;
	std::cout << "End announce" << std::endl;
}

void IRCServer::start()
{
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;        // указатель на результаты

	FD_ZERO(&_master_set);
	init_cmds(this);

	memset(&hints, 0, sizeof hints); // убедимся, что структура пуста
	hints.ai_family = AF_UNSPEC;        // неважно, IPv4 или IPv6
	hints.ai_socktype = SOCK_STREAM;    // TCP stream-sockets
	hints.ai_flags = AI_PASSIVE;        // заполните мой IP-адрес за меня
	if ((status = getaddrinfo(NULL, _serv_Port.c_str(), &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	// servinfo теперь указывает на связанный список на одну или больше структуру addrinfo

	// получаем fd для сокета
	if ((_listener_fd = socket(servinfo->ai_family, servinfo->ai_socktype,
						  servinfo->ai_protocol)) == -1)
	{
		fprintf(stderr, "Getting socket_fd error\n");
		exit(1);
	}
	fcntl(_listener_fd, F_SETFL, O_NONBLOCK);

	// избавляемся от надоедливой ошибки «Address already in use»
	int yes = 1;
	if (setsockopt(_listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		fprintf(stderr, "setsockopt error\n");
		exit(1);
	}

	if (bind(_listener_fd, servinfo->ai_addr, servinfo->ai_addrlen) != 0)
	{
		fprintf(stderr, "Binding socket error\n");
		close(_listener_fd);
		exit(1);
	}

	freeaddrinfo(servinfo); // освобождаем связанный список
	if (listen(_listener_fd, 20) == -1)
	{
		fprintf(stderr, "listen error\n");
		exit(1);
	}
	FD_SET(_listener_fd, &_master_set);
	_fd_max = _listener_fd;
	std::cout << "Server started" << std::endl;
}

void IRCServer::work()
{
	int newfd;								// дескриптор для новых соединений
	struct sockaddr client_addr;	// адрес клиента
	socklen_t addr_size = sizeof client_addr;
	char buf[512];							// буфер для сообщения
	int nbytes, ready_fds;
	fd_set read_fds;
	timeval	timeout = {30, 0};

	FD_ZERO(&read_fds);

	for(;;)
	{
		read_fds = _master_set;
		if ((ready_fds = select(_fd_max + 1, &read_fds, NULL, NULL, &timeout)) == - 1)
		{
			perror("select error");
			exit(4);
		}
		// проходим через существующие соединения, ищем данные для чтения
		for(int i = 0; ready_fds > 0 && i <= _fd_max; i++)
		{
			if (FD_ISSET(i, &read_fds))
			{ 	// есть!
				if (i == _listener_fd)
				{
					// обрабатываем новые соединения
					addr_size = sizeof client_addr;
					newfd = accept(_listener_fd, &client_addr, &addr_size);
//					char *name;
//					name = inet_ntoa(((struct sockaddr_in *)&client_addr)->sin_addr);
//					printf("name = %s\n", name);
					fcntl(newfd, F_SETFL, O_NONBLOCK);
					if (newfd == -1)
						perror("accept error");
					else
					{
						FD_SET(newfd, &_master_set); // добавляем в мастер-сет
//						Client ss(newfd);
						_client_list.insert(std::pair<int, Client*>(newfd, new Client(newfd)));
						_client_buffer_in.insert(std::pair<int, std::string>(newfd,std::string()));
						_client_buffer_out.insert(std::pair<int, std::string>(newfd,std::string()));
						if (newfd > _fd_max)
							_fd_max = newfd;
					}
					std::cout << "IRC: new connection on socket " << newfd << std::endl;
				}
				else
				{
					// обрабатываем данные клиента
					if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0)
					{
						// получена ошибка или соединение закрыто клиентом
						if (nbytes == 0)
                        {
							// соединение закрыто
						    //delete getClient(i);
                            getClient(i)->leaveChannels();
						    _client_list.erase(i);
							printf("IRC: socket %d closed\n", i);
                        }
						else
							perror("recv error");
						close(i); 				// bye!
						FD_CLR(i, &_master_set); // удаляем из мастер-сета
					}
					else
					{
						buf[nbytes] = '\0';
//                        printf("MSG = %s", buf);
						std::cout << "IRC: new msg from " << _client_list.find(i)->second->getfd() << std::endl;
						_client_buffer_in.find(i)->second.append(buf);
						_processing_msg(_client_buffer_in.find(i)->second, i, nbytes);
					}
				}
				ready_fds--;
			}
		}
	}
}

void IRCServer::_processing_msg(std::string buffer, int fd, int nbytes)
{
	unsigned long pos;

	while ((pos = buffer.find("\r\n", 0)) != std::string::npos)
	{
		Msg msg(buffer.substr(0, pos));
		_client_buffer_in.find(fd)->second.erase(0, pos + 2);
		buffer.erase(0, pos + 2);
		if(_cmds.find(msg.getMsgCommand()) != _cmds.end())
			if (msg.getMsgCommand() == "USER" || msg.getMsgCommand() == "NICK" ||
					msg.getMsgCommand() == "PASS" || !_client_list.find(fd)->second->getRealName().empty())
			_cmds[msg.getMsgCommand()](fd, msg.get_params(), this);
	}
	buffer.clear();
}

Client *IRCServer::getClient(int fd) {
    std::map<int, Client*>::iterator it;
    it = _client_list.find(fd);
    if (it != _client_list.end())
        return (it->second);
    return (nullptr);
}

Client *IRCServer::getClientByName(const std::string& name) {
    for (int j = 0; j <= _fd_max; j++)
    {
        if (FD_ISSET(j, &_master_set))
        {
            Client *client = getClient(j);
            if (client != nullptr && client->getName() == name)
                return (client);
		}
    }
    return (nullptr);
}

Channel *IRCServer::getChannel(std::string name) {
    std::map<std::string, Channel*>::iterator it;
    it = _channel_list.find(name);
    if (it != _channel_list.end())
        return (it->second);
    return (nullptr);
}

void IRCServer::addChannel(std::string name, int fd) {
    Channel *channel = getChannel(name);
    if (channel == nullptr)
        _channel_list[name] = new Channel(name, fd, this);
    else
        channel->AddClient(fd);
}

const std::string &IRCServer::getServPass() const
{
	return _serv_pass;
}

