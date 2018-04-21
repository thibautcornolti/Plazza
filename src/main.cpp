/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include <chrono>
#include <iostream>
#include <thread>

#include "classes/Parser.hpp"
#include "classes/Slave.hpp"
#include "classes/Task.hpp"
#include "classes/Worker.hpp"

int main(int ac, char **av)
{
	if (ac > 2)
		return 84;
	Plazza::Parser p;
	bool hasTasks = true;

	while (hasTasks) {
		auto task = p.getNextTask();
		hasTasks = !(task.getType() == Plazza::Task::Type::EXIT);
		std::cout << task << std::endl;
	}
	return (EXIT_SUCCESS);
}
