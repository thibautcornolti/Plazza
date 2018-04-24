/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <memory>
#include "Slave.hpp"

namespace Plazza {
	class SlavePool {
		public:
			SlavePool(unsigned);
			~SlavePool();

			void pushTask(Task &);
			void createSlave();
			Slave &getBestSlave();
			unsigned getTotalPower();
			unsigned getAvailablePower();

		protected:
		private:
			unsigned _workerCount;
			std::vector<std::unique_ptr<Slave>> _slaves;
	};
};
