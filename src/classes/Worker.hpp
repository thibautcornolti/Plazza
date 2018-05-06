/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <unistd.h>

#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

#include "Scrapper.hpp"
#include "Task.hpp"
#include "TaskPusherizer.hpp"
#include "socket/ClientUnixSocket.hpp"

namespace Plazza {
	class Worker : public TaskPusherizer {
	public:
		Worker(size_t, size_t, const std::string &);
		~Worker();

		bool isWorking();
		bool isRunning() const;
		unsigned getLoad();
		Task getTask();
		void join();
		void pushTask(const Task);

	protected:
	private:
		void _run();
		void _parse(Plazza::Task &);

		size_t _slaveID;
		size_t _workerID;
		std::thread _thread;
		std::mutex _mutex;
		std::condition_variable _threadCond;
		std::queue<Plazza::Task> _tasks;
		Plazza::Task _currentTask;
		ClientUnixSocket _logger;
		bool _isWorking;
		bool _isRunning;
		std::string _loggerName;
	};
}
