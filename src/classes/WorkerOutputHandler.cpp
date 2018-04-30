/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "WorkerOutputHandler.hpp"

Plazza::WorkerOutputHandler::WorkerOutputHandler()
	: _hasToExit(false),
	  _path(".sockets/wouthandler_" +
		  std::to_string(getpid() * time(NULL)) + ".sock"),
	  _clients(0)
{
	_thread = std::thread(&Plazza::WorkerOutputHandler::_run, this);
}

Plazza::WorkerOutputHandler::~WorkerOutputHandler()
{
	_hasToExit = true;
	_thread.join();
}

std::string Plazza::WorkerOutputHandler::getPath()
{
	return _path;
}

void Plazza::WorkerOutputHandler::_run()
{
	mkdir(".sockets", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	_server = ServerUnixSocket(_path);
	while (!_hasToExit) {
		_waitEvent();
		printf("unblock!\n");
		if (_server.isDataPending()) {
			printf("connected!\n");
			_clients.push_back(_server.accept());
			continue;
		}
		for (auto &client : _clients) {
			while (client.isDataPending())
				printf("%s\n", client.receive().c_str());
		}
	}
	_server.close();
	remove(_path.c_str());
}

void Plazza::WorkerOutputHandler::_waitEvent()
{
	std::vector<struct pollfd> fds;

	fds.reserve(_clients.size());
	for (size_t i = 0; i < _clients.size(); i++)
		fds.push_back(pollfd{.fd = _clients.at(i).getHandle(),
			.events = POLLIN,
			.revents = 0});
	fds.push_back(pollfd{
		.fd = _server.getHandle(), .events = POLLIN, .revents = 0});
	poll(&fds[0], fds.size(), 1000);
}
