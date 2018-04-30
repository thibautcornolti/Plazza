/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientUnixSocket
*/

#include "ClientUnixSocket.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

ClientUnixSocket::ClientUnixSocket() : UnixSocket()
{
}

ClientUnixSocket::ClientUnixSocket(const std::string &path)
	: UnixSocket()
{
	ClientUnixSocket::connect(path);
}

ClientUnixSocket::ClientUnixSocket(int fd) : UnixSocket(fd)
{
}

ClientUnixSocket::~ClientUnixSocket()
{
}

bool ClientUnixSocket::connect(const std::string &path)
{
	struct sockaddr_un addr;

	memcpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);
	addr.sun_family = AF_UNIX;
	if (::connect(_socket, (const sockaddr *)&addr, sizeof(addr)) != 0)
		return false;
	return true;
}
