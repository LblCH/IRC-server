#include "Server.hpp"

int main(int argc, char **argv)
{
	IRCServer server(argc, argv);
//	server.announce();
	server.start();
	server.work();
	return 0;
}
