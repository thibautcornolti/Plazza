/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdexcept>

#include "socket/SocketPair.hpp"
#include "socket/UnixSocket.hpp"

class Fork {
public:
	Fork();
	~Fork();

	bool isChild();
	int getPid();
	int getOtherPid();
	UnixSocket &getSocket();
	unsigned char wait();

protected:
private:
	int _otherPid = 0;
	int _pid = 0;
	UnixSocket _socket;
	bool _isChild = false;
};
