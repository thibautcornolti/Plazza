/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** SocketPair
*/

#pragma once

template <class T> class SocketPair {
public:
	SocketPair(int domain, int type, int protocol);
	~SocketPair();
	T get(size_t idx);
	void close(size_t idx);

protected:
	int _fds[2];

private:
};

#include "SocketPair.tpp"
