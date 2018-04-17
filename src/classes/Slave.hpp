/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#pragma once

#include "Task.hpp"

namespace Plazza {
	class Slave {
		public:
			Slave(unsigned);
			~Slave();

			void pushTask(Task &);

		protected:
		private:
			unsigned int _threadCount;
	};
};
