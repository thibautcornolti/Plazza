/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** UnixSocket
*/

#pragma once

#include <sys/socket.h>

#include "Socket.hpp"

class UnixSocket : public Socket {
public:
	UnixSocket();
	UnixSocket(int fd);
	~UnixSocket();

protected:
private:
};
