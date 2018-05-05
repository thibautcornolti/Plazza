/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Socket
*/

#pragma once

#include "ISocket.hpp"

class Socket : public ISocket {
public:
	Socket(int domain, int type, int protocol);
	Socket(int fd);
	~Socket();
	void close() override;
	bool waitData(int timeout) override;
	bool isDataPending() override;
	std::string receive() override;
	void send(std::string msg) override;
	int getHandle() override;

protected:
	int _socket;
	std::string _buffer;

private:
	static void _sigPipeHandler(int);
};
