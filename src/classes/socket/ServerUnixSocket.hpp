/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ServerUnixSocket
*/

#pragma once

#include "UnixSocket.hpp"
#include <string>

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
