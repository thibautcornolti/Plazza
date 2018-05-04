/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Fork.hpp"
#include "socket/SocketPair.hpp"
#include <sys/socket.h>
#include <sys/wait.h>

Fork::Fork() : _otherPid(getpid())
{
	SocketPair<UnixSocket> pair(AF_UNIX, SOCK_STREAM, 0);
	int pid = fork();

	if (pid < 0)
		throw std::runtime_error("fork failed");
	else if (pid) {
		_otherPid = pid;
		_socket = pair.get(1);
		pair.close(0);
	}
	else {
		_isChild = true;
		_socket = pair.get(0);
		pair.close(1);
	}
	_pid = getpid();
}

Fork::~Fork()
{
	if (isChild()) {
		dprintf(2, "__EXIT__\n");
		exit(0);
	}
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

UnixSocket &Fork::getSocket()
{
	return _socket;
}

unsigned char Fork::wait()
{
	int ret = 0;

	if (Fork::isChild() == false) {
		waitpid(_otherPid, &ret, 0);
		ret = WIFEXITED(ret) ? WEXITSTATUS(ret) : (ret % 128 + 128);
	}
	return ret;
}
