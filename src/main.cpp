/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include <chrono>
#include <iostream>
#include <thread>
#include "classes/SlavePool.hpp"
#include "classes/Slave.hpp"
#include "classes/Parser.hpp"
#include "classes/Task.hpp"
#include "classes/Worker.hpp"

int main(int ac, char **av)
{
	if (ac > 2)
		return 84;
	Plazza::Parser p;
	Plazza::SlavePool pool(1);
	bool hasTasks = true;

	while (hasTasks) {
		auto task = p.getNextTask();
		hasTasks = !(task.getType() == Plazza::Task::Type::EXIT);
		std::cout << task << std::endl;
		pool.pushTask(task);
	}
	return (EXIT_SUCCESS);
}
