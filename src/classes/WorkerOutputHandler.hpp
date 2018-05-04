/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <unistd.h>
#include <poll.h>
#include <sys/stat.h>
#include <vector>
#include <list>
#include <thread>
#include <condition_variable>
#include <string>
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

	protected:
	private:
		void _run();
		void _waitEvent();

		bool _hasToExit;
		std::thread _thread;
		std::condition_variable _threadCond;
		std::string _path;
		ServerUnixSocket _server;
		std::vector<UnixSocket> _clients;
		std::list<std::string> _logs;
	};
};
