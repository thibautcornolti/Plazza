/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** TCPSocket
*/

#pragma once

#include "Socket.hpp"

class TCPSocket : public Socket {
public:
	TCPSocket();
	TCPSocket(int fd);
	~TCPSocket();

protected:
private:
};
