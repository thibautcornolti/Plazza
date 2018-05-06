/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** TCPSocket
*/

#pragma once

#include <netdb.h>
#include <sys/socket.h>

#include "Socket.hpp"

class TCPSocket : public Socket {
public:
	TCPSocket();
	TCPSocket(int fd);
	~TCPSocket();

protected:
private:
};
