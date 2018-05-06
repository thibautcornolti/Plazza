/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** UnixSocket
*/

#include "UnixSocket.hpp"

UnixSocket::UnixSocket() : Socket(AF_UNIX, SOCK_STREAM, 0)
{
}

UnixSocket::UnixSocket(int fd) : Socket(fd)
{
}

UnixSocket::~UnixSocket()
{
}
