/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Socket
*/

#include "Socket.hpp"
#include <errno.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket(int domain, int type, int protocol)
	: _socket(socket(domain, type, protocol))
{
}

Socket::Socket(int fd) : _socket(fd)
{
}

Socket::~Socket()
{
}

void Socket::close()
{
	if (_socket != 0) {
		::close(_socket);
		_socket = 0;
	}
}

bool Socket::waitData(int timeout)
{
	struct pollfd s {
		.fd = _socket, .events = POLLIN, .revents = 0
	};

	if (_socket == 0)
		return false;
	while (1) {
		int ret = poll(&s, 1, timeout);
		if (!(ret == -1 && errno == EAGAIN))
			continue;
		return (ret == 0 && (s.revents & POLLIN) == POLLIN);
	}
	return false;
}

bool Socket::isDataPending()
{
	return Socket::waitData(0);
}

std::string Socket::receive()
{
	char buffer[1025] = {0};
	static std::string s = "";

	while (strchr(s.c_str(), '\n') == 0) {
		int size = read(_socket, buffer, 1024);
		if (size == -1) printf("errno: %d\n", errno);
		buffer[size] = 0;
		// printf("buffer: '%s'\n", buffer);
		s += buffer;
	}
	int idx = strchr(s.c_str(), '\n') - s.c_str();
	std::string c = "";
	c.reserve(idx);
	for (int i = 0; i < idx; i++)
		c += s[i];
	s = &(s[idx + 1]);
	return c;
}

void Socket::send(std::string msg)
{
	::write(_socket, msg.c_str(), msg.size());
}

int Socket::getHandle()
{
	return _socket;
}
