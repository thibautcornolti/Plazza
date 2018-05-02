/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "socket/ServerTCPSocket.hpp"
#include <functional>
#include <poll.h>
#include <regex>
#include <string.h>
#include <vector>

class WebServer {
public:
	using Router = std::function<std::string(
		const std::string &method, const std::string &path)>;

	WebServer(const std::string &, int, const Router &router);
	WebServer() = default;
	~WebServer();

	void launch(bool &);

protected:
private:
	void _waitEvent();
	void _ingestHeader(const std::string &);

	std::string _ip;
	int _port;
	ServerTCPSocket _socket;
	std::vector<TCPSocket> _sockets;
	Router _router;
	std::string _lastMethod;
	std::string _lastPath;
};
