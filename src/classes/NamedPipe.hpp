/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** NamedPipe
*/

#pragma once

#include <string>
#include <fcntl.h>

class NamedPipe {
public:
	enum Permissions { READ = O_RDONLY, WRITE = O_WRONLY, RDWR = O_RDWR };
	NamedPipe(const std::string &name, Permissions fdPermission,
		mode_t fifoPermission);
	NamedPipe(const std::string &name, Permissions fdPermission);
	NamedPipe(int fd);
	~NamedPipe();
	void close();
	bool waitData(int timeout) const;
	bool isDataPending() const;
	std::string receive();
	void send(std::string msg) const;
	int getHandle() const;
	void remove() const;

protected:
private:
	int _fd;
	std::string _name;
	std::string _buffer;
	Permissions _permission;
};
