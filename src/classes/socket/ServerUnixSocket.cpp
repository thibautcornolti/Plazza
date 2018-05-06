/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ServerUnixSocket
*/

#include "ServerUnixSocket.hpp"

ServerUnixSocket::ServerUnixSocket() : UnixSocket()
{
}

ServerUnixSocket::ServerUnixSocket(const std::string &path) : UnixSocket()
{
	if (ServerUnixSocket::listen(path) == false)
		throw std::runtime_error("listen error");
}

ServerUnixSocket::ServerUnixSocket(int fd) : UnixSocket(fd)
{
}

ServerUnixSocket::~ServerUnixSocket()
{
}

bool ServerUnixSocket::listen(const std::string &path)
{
	sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_path, path.c_str(),
		std::min(sizeof(addr.sun_path) - 1, path.size()));
	return ::bind(_socket, (const sockaddr *)&addr, sizeof(addr)) == 0 &&
		::listen(_socket, 1024) == 0;
}

UnixSocket ServerUnixSocket::accept()
{
	int fd = ::accept(_socket, 0, 0);

	if (fd == -1)
		throw std::exception();
	return UnixSocket(fd);
}
