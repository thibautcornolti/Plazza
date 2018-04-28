/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <string>

class ISocket {
public:

	virtual void close() = 0;
	virtual bool waitData(int timeout) = 0;
	virtual bool isDataPending() = 0;
	virtual std::string receive() = 0;
	virtual void send(std::string msg) = 0;
	virtual int getHandle() = 0;

protected:
private:
};
