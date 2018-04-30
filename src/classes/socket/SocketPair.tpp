/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** SocketPair
*/

#pragma once

template <class T>
SocketPair<T>::SocketPair(int domain, int type, int protocol)
{
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
