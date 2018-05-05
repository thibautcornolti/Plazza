/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** WorkerPool
*/

#pragma once

#include "TaskPusherizer.hpp"
#include "Worker.hpp"
#include <cstddef>
#include <vector>

namespace Plazza {
	class WorkerPool : public TaskPusherizer {
	public:
		WorkerPool() = default;
		WorkerPool(size_t, size_t, const std::string &);
		~WorkerPool();
		void pushTask(const Plazza::Task) override;
		unsigned getLoad();
		std::vector<size_t> getSummaryLoad();
		std::vector<Plazza::Task> getSummaryTask();
		void exit();

	protected:
	private:
		size_t _id;
		Plazza::Worker &getBestWorker();
		size_t _threadCount;
		std::vector<std::unique_ptr<Plazza::Worker>> _workers;
		std::string _loggerName;
	};
};
