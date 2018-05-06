/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <poll.h>
#include <sys/stat.h>
#include <unistd.h>

#include <condition_variable>
#include <fstream>
#include <list>
#include <string>
#include <thread>
#include <vector>

#include "socket/ServerUnixSocket.hpp"

namespace Plazza {
	class WorkerOutputHandler {
	public:
		WorkerOutputHandler();
		~WorkerOutputHandler();

		std::string getPath();
		bool hasLogPending();
		std::string getLogLine();
		void popLogLine();
		void stop();

	protected:
	private:
		void _run();
		void _listenNewClients();
		void _readClients();
		void _waitEvent();

		bool _hasToStop;
		bool _isRunning;
		std::thread _thread;
		std::condition_variable _threadCond;
		std::string _path;
		ServerUnixSocket _server;
		std::vector<UnixSocket> _clients;
		std::list<std::string> _logs;
		std::fstream _logfile;
	};
};
