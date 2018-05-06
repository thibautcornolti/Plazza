/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ServerTCPSocket
*/

#include "ServerTCPSocket.hpp"

ServerTCPSocket::ServerTCPSocket() : TCPSocket()
{
}

ServerTCPSocket::ServerTCPSocket(const std::string &ip, int port) : TCPSocket()
{
	if (ServerTCPSocket::listen(ip, port) == false)
		throw std::runtime_error("listen error");
}

ServerTCPSocket::ServerTCPSocket(int fd) : TCPSocket(fd)
{
}

ServerTCPSocket::~ServerTCPSocket()
{
}

bool ServerTCPSocket::listen(const std::string &ip, int port)
{
	sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	return ::bind(_socket, (const sockaddr *)&addr, sizeof(addr)) == 0 &&
		::listen(_socket, 1024) == 0;
}

TCPSocket ServerTCPSocket::accept()
{
	int fd = ::accept(_socket, 0, 0);

	if (fd == -1)
		throw std::exception();
	return TCPSocket(fd);
}
