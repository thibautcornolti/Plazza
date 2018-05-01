/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "socket/UnixSocket.hpp"
#include "ForkedSlave.hpp"
#include <unistd.h>
#include <stdexcept>

class Fork {
	public:
		Fork();
		~Fork();

		bool isChild();
		int getPid();
		int getOtherPid();
		UnixSocket &getSocket();

	protected:
	private:
		int _otherPid = 0;
		int _pid = 0;
		UnixSocket _socket;
		bool _isChild = false;
};
