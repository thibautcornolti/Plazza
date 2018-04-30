/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#pragma once

#include "Task.hpp"
#include "Worker.hpp"
#include "WorkerPool.hpp"

namespace Plazza {
	class ForkedSlave {
		public:
			ForkedSlave(unsigned);
			~ForkedSlave();

			void pushTask(Task &);
			unsigned getLoad();
			unsigned getTotalPower();
			unsigned getAvailablePower();

		protected:
		private:
			Worker &getBestWorker();

			unsigned int _workerCount;
			WorkerPool _pool;
	};
};