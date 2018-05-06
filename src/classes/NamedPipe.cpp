/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** NamedPipe
*/

#include "NamedPipe.hpp"

NamedPipe::NamedPipe(const std::string &name, Permissions fdPermission,
	mode_t fifoPermission)
	: _fd(0), _name(name), _permission(fdPermission)
{
	if (mkfifo(name.c_str(), fifoPermission)) {
		std::ostringstream oss;
		oss << "Named Pipe: " << strerror(errno);
		throw std::runtime_error(oss.str());
	}
	_fd = open(name.c_str(), fdPermission);
	if (_fd == -1) {
		std::ostringstream oss;
		oss << "Named Pipe: " << strerror(errno);
		throw std::runtime_error(oss.str());
	}
}

NamedPipe::NamedPipe(const std::string &name, Permissions fdPermission)
	: _fd(open(name.c_str(), fdPermission)), _name(name),
	  _permission(fdPermission)
{
	if (_fd == -1) {
		std::ostringstream oss;
		oss << "Named Pipe: " << strerror(errno);
		throw std::runtime_error(oss.str());
	}
}

NamedPipe::NamedPipe(int fd) : _fd(fd)
{
}

NamedPipe::~NamedPipe()
{
}

void NamedPipe::close()
{
	if (_fd != 0) {
		::close(_fd);
		_fd = 0;
	}
}

bool NamedPipe::waitData(int timeout) const
{
	struct pollfd s {
		.fd = _fd, .events = POLLIN, .revents = 0
	};

	if (_fd == 0)
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

bool NamedPipe::isDataPending() const
{
	return _buffer.size() != NamedPipe::waitData(0);
}

std::string NamedPipe::receive()
{
	char buffer[2] = {0};

	while (strchr(_buffer.c_str(), '\n') == 0) {
		int size = ::read(_fd, buffer, 1);
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

void NamedPipe::send(std::string msg) const
{
	::write(_fd, msg.c_str(), msg.size());
}

int NamedPipe::getHandle() const
{
	return _fd;
}

void NamedPipe::remove() const
{
	if (_name.size())
		unlink(_name.c_str());
}
