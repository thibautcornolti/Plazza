/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "Slave.hpp"

namespace Plazza {
	class SlavePool {
		public:
			SlavePool();
			~SlavePool();

			void pushTask(Task &);
			Slave &getBestSlave();
		protected:
		private:
			std::vector<Slave> _slaves;
	};
};
