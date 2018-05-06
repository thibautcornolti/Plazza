/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ServerTCPSocket
*/

#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#include <stdexcept>
#include <string>

#include "TCPSocket.hpp"

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
