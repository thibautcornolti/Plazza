/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** SocketPair
*/

#pragma once

#include <sys/socket.h>

template <class T>
SocketPair<T>::SocketPair(int domain, int type, int protocol)
{
	if (socketpair(domain, type, protocol, _fds))
		throw std::runtime_error("socketpair failure");
}

template <class T> SocketPair<T>::~SocketPair()
{
}

template <class T> T SocketPair<T>::get(size_t idx)
{
	return T(_fds[idx]);
}

template <class T> void SocketPair<T>::close(size_t idx)
{
	close(_fds[idx]);
}
