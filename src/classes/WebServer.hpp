/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <string.h>
#include <poll.h>
#include <vector>
#include "socket/ServerTCPSocket.hpp"

class WebServer {
public:
	WebServer(const std::string &, int);
	WebServer() = default;
	~WebServer();

	void launch();

protected:
private:
	void _waitEvent();

	std::string _ip;
	int _port;
	ServerTCPSocket _socket;
	std::vector<TCPSocket> _sockets;
};
