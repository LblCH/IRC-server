#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXDATASIZE 100 // максимальное число байт, принимаемых за один раз

// получение структуры sockaddr, IPv4 или IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	if (argc != 3) {
		printf("usage: client <hostname> <port>");
		exit(1);
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
		printf("getaddrinfo: %s", gai_strerror(rv));
		return 1;
	}

// Проходим через все результаты и соединяемся к первому возможному
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
							 p->ai_protocol)) == - 1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == - 1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}

	if (p == NULL) {
		printf("client: failed to connecting");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			  s, sizeof s);
	printf("bot: connecting to %s\n", s);

	freeaddrinfo(servinfo); // эта структура больше не нужна

	std::string stroka;
	send(sockfd, "NICK bot\r\nUSER bot 0 * botovich\r\nJOIN #bot\r\n", 50, 0);
	while(1)
	{
		if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1)
		{
			perror("recv");
			exit(1);
		}
		buf[numbytes] = '\0';
		printf("client: received %s",buf);
		stroka = buf;
		if (stroka.find("PRIVMSG #bot :bot") != std::string::npos)
		{
			printf("test\n");
			send(sockfd, "PRIVMSG #bot :Hello im a so simple bot!\r\n", 43, 0);
		}
	}


	close(sockfd);

	return 0;
}