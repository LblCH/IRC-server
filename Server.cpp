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
	// std::cout << "Destrunct serv" << std::endl;
}

void Server::anonce()
{
	std::cout << "Start anonce" << std::endl;
	std::cout << "serv_host_name : "  <<_serv_host_name  << std::endl;
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
	while (_key == 0)
	{
		// port listen
		// msg read/post
	}
}