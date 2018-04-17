/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "classes/Task.hpp"
#include "classes/Slave.hpp"

int main(void)
{
	Plazza::Slave slave(3);
	Plazza::Task task(Plazza::Task::SCRAP);
	Plazza::Task taske(Plazza::Task::EXIT);

	slave.pushTask(task);
	slave.pushTask(task);
	slave.pushTask(task);
	slave.pushTask(task);
	return (EXIT_SUCCESS);
}