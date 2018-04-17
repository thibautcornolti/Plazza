/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "classes/Worker.hpp"

int main(void)
{
	Plazza::Worker worker;
	Plazza::Task task(Plazza::Task::SCRAP);
	Plazza::Task taske(Plazza::Task::EXIT);

	worker.pushTask(task);
	worker.pushTask(task);
	worker.pushTask(task);
	worker.pushTask(task);
	return (EXIT_SUCCESS);
}