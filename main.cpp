#include "Server.hpp"

int main()
{
	Server server("./config.txt");
	server.announce();
	server.start();
//	std::cout << "Hello, World!" << std::endl;
	return 0;
}
