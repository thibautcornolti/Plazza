/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Socket
*/

#include "Socket.hpp"
#include <errno.h>
#include <poll.h>
#include <signal.h>
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
	signal(SIGPIPE, &_sigPipeHandler);
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
		errno = 0;
		int ret = poll(&s, 1, timeout);
		if (ret == -1 && errno == EAGAIN)
			continue;
		return (ret == 1 && (s.revents & POLLIN) == POLLIN);
	}
	return false;
}

bool Socket::isDataPending()
{
	return _buffer.size() != Socket::waitData(0);
}

std::string Socket::receive()
{
	char buffer[2] = {0};

	while (strchr(_buffer.c_str(), '\n') == 0) {
		int size = read(_socket, buffer, 1);
		if (size == -1)
			printf("errno: %d\n", errno);
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

void Socket::_sigPipeHandler(int)
{
}
