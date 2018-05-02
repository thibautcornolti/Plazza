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
		WorkerPool(size_t);
		~WorkerPool();
		void pushTask(const Plazza::Task) override;
		unsigned getLoad();
		unsigned getTotalPower();
		unsigned getAvailablePower();
		void exit();

	protected:
	private:
		Plazza::Worker &getBestWorker();
		size_t _threadCount;
		std::vector<std::unique_ptr<Plazza::Worker>> _workers;
	};
};
