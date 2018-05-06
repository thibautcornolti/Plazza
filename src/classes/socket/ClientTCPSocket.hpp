/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientTCPSocket
*/

#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#include <string>

#include "TCPSocket.hpp"

class ClientTCPSocket : public TCPSocket {
public:
	ClientTCPSocket();
	ClientTCPSocket(const std::string &host, int port);
	ClientTCPSocket(int fd);
	~ClientTCPSocket();
	bool connect(const std::string &host, int port);

protected:
private:
};
