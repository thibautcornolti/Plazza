/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "WorkerOutputHandler.hpp"

Plazza::WorkerOutputHandler::WorkerOutputHandler()
	: _isRunning(false), _hasToStop(false),
	  _path(".sockets/wouthandler_" +
		  std::to_string(getpid() * time(NULL)) + ".sock"),
	  _clients(0), _logs(0)
{
	std::mutex m;
	std::unique_lock<std::mutex> lk(m);
	_thread = std::thread(&Plazza::WorkerOutputHandler::_run, this);
	_threadCond.wait(lk);
}

Plazza::WorkerOutputHandler::~WorkerOutputHandler()
{
	stop();
}

std::string Plazza::WorkerOutputHandler::getPath()
{
	return _path;
}

bool Plazza::WorkerOutputHandler::hasLogPending()
{
	return _logs.size() > 0;
}

std::string Plazza::WorkerOutputHandler::getLogLine()
{
	return _logs.front();
}

void Plazza::WorkerOutputHandler::popLogLine()
{
	_logs.pop_front();
}

void Plazza::WorkerOutputHandler::stop()
{
	_hasToStop = true;
	if (_thread.joinable() && _isRunning)
		_thread.join();
}

void Plazza::WorkerOutputHandler::_run()
{
	std::fstream logfile("plazza.log",
		std::fstream::in | std::fstream::app | std::fstream::ate);
	_isRunning = true;
	mkdir(".sockets", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	_server = ServerUnixSocket(_path);
	while (!_hasToStop) {
		_threadCond.notify_all();
		_waitEvent();
		_listenNewClients();
		_readClients();
	}
	_server.close();
	logfile.close();
	remove(_path.c_str());
	_isRunning = false;
}

void Plazza::WorkerOutputHandler::_listenNewClients()
{
	if (_server.isDataPending())
		_clients.push_back(_server.accept());
}

void Plazza::WorkerOutputHandler::_readClients()
{
	std::vector<UnixSocket> cl;

	cl.reserve(_clients.size());
	for (auto &client : _clients) {
		std::string received;
		try {
			while (client.isDataPending()) {
				received = client.receive();
				dprintf(1, "%s\n", received.c_str());
				if (_logfile.is_open())
					_logfile << received << std::endl;
				_logs.push_back(received);
			}
			cl.emplace_back(client);
		}
		catch (std::exception) {
			client.close();
		}
	}
	_clients = cl;
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
