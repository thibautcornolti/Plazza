/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientTCPSocket
*/

#pragma once

#include "TCPSocket.hpp"
#include <string>

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
