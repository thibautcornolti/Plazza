/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ServerUnixSocket
*/

#pragma once

#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdexcept>
#include <string>

#include "UnixSocket.hpp"

class ServerUnixSocket : public UnixSocket {
public:
	ServerUnixSocket();
	ServerUnixSocket(const std::string &);
	ServerUnixSocket(int);
	~ServerUnixSocket();
	bool listen(const std::string &);
	UnixSocket accept();

protected:
private:
};
