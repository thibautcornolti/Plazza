/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientUnixSocket
*/

#include "ClientUnixSocket.hpp"
#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

ClientUnixSocket::ClientUnixSocket() : UnixSocket()
{
}

ClientUnixSocket::ClientUnixSocket(const std::string &path) : UnixSocket()
{
	if (!ClientUnixSocket::connect(path))
		throw std::runtime_error("connect failed");
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

	memset(&addr, 0, sizeof(addr));
	memcpy(addr.sun_path, path.c_str(),
		std::min(path.size(), sizeof(addr.sun_path) - 1));
	addr.sun_family = AF_UNIX;
	if (::connect(_socket, (const sockaddr *)&addr, sizeof(addr)) != 0)
		return false;
	return true;
}
