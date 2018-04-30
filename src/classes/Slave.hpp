/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#pragma once

#include "Fork.hpp"
#include "ForkedSlave.hpp"
#include "Task.hpp"
#include "TaskPusherizer.hpp"
#include "Worker.hpp"
#include "WorkerPool.hpp"

namespace Plazza {
	class Slave : public TaskPusherizer {
	public:
		Slave(unsigned);
		~Slave();

		void pushTask(Task &);
		unsigned getLoad();
		unsigned getTotalPower();
		unsigned getAvailablePower();

	protected:
	private:
		Worker &getBestWorker();
		WorkerPool _pool;
		Fork _fork;
	};
};
