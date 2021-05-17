//
// Created by Adeline Vivien on 4/24/21.
//

#include "Server.hpp"

Server::Server(std::string file)
{
	std::ifstream input_file;
	input_file.open(file);
	if (input_file.is_open())
	{
		std::string s; // parse string config file
		int count = 0;
		while(getline(input_file, s))
		{
			if (s.find('#') == -1 && s.length() > 3) //  skipping comments and empty string
			{
				count++;
				s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
				s.erase(0, s.find('=') + 1);
				if (count == 1) _serv_host_name = s;
				if (count == 2) _serv_ip_serv = s;
				if (count == 3) _geographic_location = s;
				if (count == 4) _serv_Port = s;
				if (count == 5) _serv_SIDl = s;
				if (count == 6) _count_all_server = atoi(s.c_str());
				if (count == 7) _serv_admin_location_info = s;
				if (count == 8) _serv_admin_email = s;
				if (count == 9) _serv_admin_other_inform = s;
				if (count == 10) _serv_network_name = s;
				if (count == 11) _serv_port = atoi(s.c_str());
				if (count == 12) _serv_directory = s;
			}
		}
	}
	else
	{
		std::cout << "Invalid file name! Load default params" << std::endl;
	}
	_key = 0;
}

Server::~Server()
{
	std::cout << "Destruct serv" << std::endl;
}

void Server::announce()
{
	std::cout << "Start anonce" << std::endl;
	std::cout << "serv_host_name : "  << _serv_host_name  << std::endl;
	std::cout << "serv_ip_serv serv : " << _serv_ip_serv  << std::endl;
	std::cout << "geographic_location serv : " << _geographic_location  << std::endl;
	std::cout << "serv_Port serv : " << _serv_Port  << std::endl;
	std::cout << "serv_SIDl serv : "<<  _serv_SIDl  << std::endl;
	std::cout << "count_all_server serv : " << _count_all_server  << std::endl;
	std::cout << "serv_admin_location_info serv : " << _serv_admin_location_info  << std::endl;
	std::cout << "serv_admin_email serv : " << _serv_admin_email  << std::endl;
	std::cout << "serv_admin_other_inform serv : "<<  _serv_admin_other_inform  << std::endl;
	std::cout << "serv_network_name serv : " << _serv_network_name  << std::endl;
	std::cout << "serv_port serv : " << _serv_port  << std::endl;
	std::cout << "serv_directory serv : " << _serv_directory  << std::endl;
	std::cout << "End anonce" << std::endl;
}

void Server::start()
{
//	while (_key == 0)
//	{
		int status;
		struct addrinfo hints;
		struct addrinfo *servinfo;  		// указатель на результаты

		memset(&hints, 0, sizeof hints); // убедимся, что структура пуста
		hints.ai_family = AF_UNSPEC;    	// неважно, IPv4 или IPv6
		hints.ai_socktype = SOCK_STREAM; 	// TCP stream-sockets
		hints.ai_flags = AI_PASSIVE;     	// заполните мой IP-адрес за меня
		if ((status = getaddrinfo(NULL, _serv_Port.c_str(), &hints, &servinfo)) != 0)
		{
			fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
			exit(1);
		}
		// servinfo теперь указывает на связанный список на одну или больше структуру addrinfo

		int sock_fd;
		// получаем fd для сокета
		if ((sock_fd = socket(servinfo->ai_family, servinfo->ai_socktype,servinfo->ai_protocol)) == -1)
		{
			fprintf(stderr, "Getting socket_fd error\n");
			exit(1);
		}

		// избавляемся от надоедливой ошибки «Address already in use»
		int yes = 1;
		if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			fprintf(stderr, "setsockopt error\n");
			exit(1);
		}

		if (bind(sock_fd, servinfo->ai_addr, servinfo->ai_addrlen) != 0)
		{
			fprintf(stderr, "Binding socket error\n");
			close(sock_fd);
			exit(1);
		}

		freeaddrinfo(servinfo); // и освобождаем связанный список
		if (listen(sock_fd, 5000) == -1)
		{
			fprintf(stderr, "listen error\n");
			exit(1);
		}

		struct sockaddr_storage client_addr;
		socklen_t addr_size = sizeof client_addr;
		int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &addr_size);
		send(client_fd, "Welcome\n", strlen("Welcome\n"), 0);

		// msg read/post
//	}
}