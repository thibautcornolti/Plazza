/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** TCPSocket
*/

#include "TCPSocket.hpp"
#include <sys/socket.h>
#include <netdb.h>

TCPSocket::TCPSocket() : Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
{
	int i = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));
}

TCPSocket::TCPSocket(int fd) : Socket(fd)
{
}

TCPSocket::~TCPSocket()
{
}
