/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "classes/Parser.hpp"
#include "classes/Slave.hpp"
#include "classes/SlavePool.hpp"
#include "classes/Task.hpp"
#include "classes/UserInterface.hpp"
#include "classes/Worker.hpp"
#include "classes/WorkerOutputHandler.hpp"
#include "classes/socket/ClientTCPSocket.hpp"
#include "classes/socket/ClientUnixSocket.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

static void atFork(Plazza::WorkerOutputHandler *output)
{
	output->stop();
}

void run(int nb, bool tty)
{
	Plazza::Parser p;
	Plazza::WorkerOutputHandler output;
	Plazza::UserInterface ui;
	Plazza::SlavePool pool(
		nb, output.getPath(), std::bind(&atFork, &output));
	if (tty)
		ui.launch(pool, output);
	while (1) {
		auto task = p.getNextTask();
		if (task.getType() == Plazza::Task::Type::EXIT)
			break;
		pool.pushTask(task);
	}
	if (tty) {
		dprintf(2, "Exiting...\n");
		ui.stop();
		dprintf(2, "Waiting for all thread to exit...\n");
	}
	pool.exit();
	output.stop();
}

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Usage: " << av[0] << " <number of thread>"
			  << std::endl;
		return EXIT_SUCCESS;
	}
	int nb = std::strtod(av[1], 0);
	if (nb <= 0) {
		std::cout << "Usage: " << av[0] << " <number of thread>"
			  << std::endl;
		return EXIT_SUCCESS;
	}
	try {
		run(nb, isatty(0));
	}
	catch (...) {
		std::cerr << "Fatal error" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
