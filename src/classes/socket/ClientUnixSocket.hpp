/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientUnixSocket
*/

#pragma once

#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <string>

#include "UnixSocket.hpp"

class ClientUnixSocket : public UnixSocket {
public:
	ClientUnixSocket();
	ClientUnixSocket(const std::string &);
	ClientUnixSocket(int);
	~ClientUnixSocket();
	bool connect(const std::string &);

protected:
private:
};
