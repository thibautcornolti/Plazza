/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ClientUnixSocket
*/

#pragma once

#include "UnixSocket.hpp"
#include <string>

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
