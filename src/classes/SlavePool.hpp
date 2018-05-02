/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <memory>
#include "Slave.hpp"
#include "TaskPusherizer.hpp"

namespace Plazza {
	class SlavePool : public TaskPusherizer {
	public:
		SlavePool(unsigned);
		~SlavePool();

		void pushTask(Task);
		void createSlave();
		Slave &getBestSlave();
		unsigned getTotalPower();
		unsigned getAvailablePower();
		void exit();

	protected:
	private:
		int _socket;
		unsigned _workerCount;
		std::vector<std::unique_ptr<Slave>> _slaves;
	};
};
