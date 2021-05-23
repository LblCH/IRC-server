#include "Server.hpp"

int main()
{
	Server server("../config.txt");
	server.announce();
	std::cout << "Hello, World!" << std::endl;
	server.start();
	std::cout << "Hello, World!" << std::endl;
	server.work();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
