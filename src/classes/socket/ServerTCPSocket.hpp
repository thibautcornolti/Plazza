/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ServerTCPSocket
*/

#pragma once

#include "TCPSocket.hpp"
#include <string>

class ServerTCPSocket : public TCPSocket {
public:
	ServerTCPSocket();
	ServerTCPSocket(const std::string &ip, int port);
	ServerTCPSocket(int fd);
	~ServerTCPSocket();
	bool listen(const std::string &ip, int port);
	TCPSocket accept();

protected:
private:
};
