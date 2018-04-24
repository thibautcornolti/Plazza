/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Fork.hpp"

Fork::Fork() : _otherPid(getpid())
{
	int pid = fork();

	if (pid < 0)
		throw std::runtime_error("fork failed");
	else if (pid)
		_otherPid = pid;
	else
		_isChild = false;
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
