/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientTCPSocket
*/

#include "ClientTCPSocket.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

ClientTCPSocket::ClientTCPSocket() : TCPSocket()
{
}

ClientTCPSocket::ClientTCPSocket(const std::string &host, int port)
	: TCPSocket()
{
	ClientTCPSocket::connect(host, port);
}

ClientTCPSocket::ClientTCPSocket(int fd) : TCPSocket(fd)
{
}

ClientTCPSocket::~ClientTCPSocket()
{
	close();
}

bool ClientTCPSocket::connect(const std::string &host, int port)
{
	struct sockaddr_in addr;
	struct addrinfo req;
	struct addrinfo *ret = 0;

	memset(&req, 0, sizeof(req));
	req.ai_family = AF_INET;
	req.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host.c_str(), 0, &req, &ret) != 0 || ret == 0)
		return false;
	addr = *(struct sockaddr_in *)ret->ai_addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if (::connect(_socket, (const sockaddr *)&addr, sizeof(addr)) != 0)
		return false;
	return true;
}
