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
#include "classes/SlavePool.hpp"

int main(void)
{
	Plazza::SlavePool pool(1);
	Plazza::Task task(Plazza::Task::SCRAP);
	Plazza::Task taske(Plazza::Task::EXIT);

	pool.pushTask(task);
	pool.pushTask(task);
	pool.pushTask(task);
	pool.pushTask(task);
	return (EXIT_SUCCESS);
}