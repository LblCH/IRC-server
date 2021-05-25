#include "Server.hpp"

int main()
{
	IRCServer server("./config.txt");
//	server.announce();
	server.start();
	server.work();
	return 0;
}
