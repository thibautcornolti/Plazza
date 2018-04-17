/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <queue>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Task.hpp"

namespace Plazza {
	class Worker {
		public:
			Worker();
			~Worker();

			bool isWorking();
			bool isRunning();
			void join();
			void pushTask(const Plazza::Task &);
		protected:
		private:
			void _run();
			void _parse();

			std::thread _thread;
			std::condition_variable _threadCond;
			std::queue<Plazza::Task> _tasks;
			bool _isWorking;
			bool _isRunning;
	};
}
