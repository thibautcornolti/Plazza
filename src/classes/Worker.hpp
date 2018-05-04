/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>
#include "Task.hpp"
#include "TaskPusherizer.hpp"
#include "socket/ClientUnixSocket.hpp"

namespace Plazza {
	class Worker : public TaskPusherizer {
	public:
		Worker(const std::string &);
		~Worker();

		bool isWorking();
		bool isRunning();
		unsigned getLoad();
		void join();
		void pushTask(const Task);

	protected:
	private:
		void _run();
		void _parse(Plazza::Task &);

		std::thread _thread;
		std::mutex _mutex;
		std::condition_variable _threadCond;
		std::queue<Plazza::Task> _tasks;
		ClientUnixSocket _logger;
		bool _isWorking;
		bool _isRunning;
		std::string _loggerName;
	};
}
