#include "Server.hpp"

int main()
{
	Server server("./config.txt");
	server.announce();
	server.start();
	server.work();
	return 0;
}
