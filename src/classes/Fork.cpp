/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Fork.hpp"
#include "socket/SocketPair.hpp"
#include <sys/socket.h>

Fork::Fork() : _otherPid(getpid())
{
	int pid = fork();
	SocketPair<UnixSocket> pair(AF_UNIX, SOCK_STREAM, 0);

	if (pid < 0)
		throw std::runtime_error("fork failed");
	else if (pid) {
		_otherPid = pid;
		_socket = pair.get(1);
		pair.close(0);
	}
	else {
		_isChild = false;
		_socket = pair.get(0);
		pair.close(1);
	}
	_pid = getpid();
}

Fork::~Fork()
{
	if (isChild())
		exit(0);
}

bool Fork::isChild()
{
	return _isChild;
}

int Fork::getPid()
{
	return _pid;
}

int Fork::getOtherPid()
{
	return _otherPid;
}
