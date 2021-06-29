#include "Server.hpp"

int main(int argc, char **argv)
{
	IRCServer server("./config.txt", argc, argv);
//	server.announce();
	server.start();
	server.work();
	return 0;
}
