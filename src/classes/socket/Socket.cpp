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
	: _socket(::socket(domain, type, protocol))
{
	if (_socket < 0)
		throw std::exception();
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
	bool ret = false;

	while (_socket && _buffer.size() == 0) {
		errno = 0;
		int state = poll(&s, 1, timeout);
		if (state == -1 && errno == EAGAIN)
			continue;
		ret = (state == 1 && (s.revents & POLLIN) == POLLIN);
	}
	return _buffer.size() != 0 || ret;
}

bool Socket::isDataPending()
{
	return _buffer.size() != 0 || Socket::waitData(0);
}

std::string Socket::receive()
{
	char buffer[2] = {0};

	while (strchr(_buffer.c_str(), '\n') == 0) {
		int size = read(_socket, buffer, 1);
		if (size == -1)
			dprintf(2, "errno: %d\n", errno);
		else if (size == 0)
			throw std::exception();
		buffer[size] = 0;
		_buffer += buffer;
	}
	int idx = strchr(_buffer.c_str(), '\n') - _buffer.c_str();
	std::string c = "";
	c.reserve(idx);
	for (int i = 0; i < idx; i++)
		c += _buffer[i];
	_buffer = &(_buffer[idx + 1]);
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
