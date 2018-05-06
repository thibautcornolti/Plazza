/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <thread>

#include "Slave.hpp"
#include "TaskPusherizer.hpp"

namespace Plazza {
	class SlavePool : public TaskPusherizer {
	public:
		SlavePool(unsigned, const std::string &,
			const std::function<void(void)> &);
		~SlavePool();

		void pushTask(Task);
		void createSlave();
		std::pair<std::unique_ptr<Slave>, std::time_t> &getBestSlave();
		unsigned getLoad();
		std::vector<std::vector<size_t>> getSummaryLoad();
		std::vector<std::vector<Plazza::Task>> getSummaryTask();
		void exit();

	protected:
	private:
		void _timeoutHandler();
		void _timeoutExitSlave(
			std::pair<std::unique_ptr<Slave>, std::time_t> &);

		int _socket;
		unsigned _workerCount;
		std::vector<std::pair<std::unique_ptr<Slave>, std::time_t>>
			_slaves;
		std::string _loggerName;
		std::function<void(void)> _atFork;
		std::thread _timeoutThread;
		bool _hasToStop;
	};
};
