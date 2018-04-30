/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "socket/UnixSocket.hpp"
#include <unistd.h>
#include <stdexcept>

class Fork {
	public:
		Fork();
		~Fork();

		bool isChild();
		int getPid();
		int getOtherPid();

	protected:
	private:
		int _otherPid = 0;
		int _pid = 0;
		UnixSocket _socket;
		bool _isChild = false;
};
