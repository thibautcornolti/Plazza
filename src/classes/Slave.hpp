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

		void pushTask(const Task);
		unsigned getLoad();
		unsigned getTotalPower();
		unsigned getAvailablePower();
		void exit();

	protected:
	private:
		void handleTask(std::istringstream &input);
		void handleLoad(std::istringstream &input);
		void handleTotalPower(std::istringstream &input);
		void handleAvailablePower(std::istringstream &input);
		void handleExit(std::istringstream &input);

		Worker &getBestWorker();
		WorkerPool _pool;
		Fork _fork;
	};
};
