/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#pragma once

#include "Fork.hpp"
#include "Task.hpp"
#include "TaskPusherizer.hpp"
#include "Worker.hpp"
#include "WorkerPool.hpp"
#include <functional>

namespace Plazza {
	class Slave : public TaskPusherizer {
	public:
		Slave(size_t, unsigned, const std::string &,
			const std::function<void(void)> &);
		~Slave();

		void launchChild();
		void pushTask(const Task);
		unsigned getLoad();
		std::vector<size_t> getSummaryLoad();
		void exit();

	protected:
	private:
		void handleTask(std::istringstream &input);
		void handleLoad(std::istringstream &input);
		void handleSummaryLoad(std::istringstream &input);
		void handleExit(std::istringstream &input);

		size_t _id;
		Worker &getBestWorker();
		WorkerPool _pool;
		Fork _fork;
		std::string _loggerName;
		std::function<void(void)> _atFork;
	};
};
