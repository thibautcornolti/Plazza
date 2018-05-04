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

static void atFork(
	Plazza::WorkerOutputHandler *output, Plazza::UserInterface *ui)
{
	dprintf(2, "atFork called\n");
	// ui->stop();
	output->stop();
}

void run()
{
	// TEST PARSER AND WORKERS
	Plazza::Parser p;
	Plazza::WorkerOutputHandler output;
	Plazza::UserInterface ui;
	Plazza::SlavePool pool(4, output.getPath(),
		std::bind(&atFork, &output, nullptr /*&ui*/));
	ui.launch(pool, output);

	while (1) {
		auto task = p.getNextTask();
		if (task.getType() == Plazza::Task::Type::EXIT)
			break;
		pool.pushTask(task);
	}
	ui.stop();

	pool.exit();
	output.stop();

	// TEST SOCKETS
	// ClientTCPSocket socket("hirevo.eu", 4444);
	// std::cout << socket.receive() << std::endl;
	// socket.send("user anonymous\r\n");
	// std::cout << socket.receive() << std::endl;
	// socket.close();

	// TEST SERIALISATION
	// COMMAND: echo "<Task Scrap toto.txt IP_ADDRESS>" | ./plazza
	// Plazza::Task out;

	// std::cout << out << std::endl;
	// std::cin >> out;
	// std::cout << out << std::endl;

	// Plazza::WorkerOutputHandler w;
	// dprintf(2, "%s\n", w.getPath().c_str());
	// ClientUnixSocket u(w.getPath());
	// u.send("oui!\n");
	// std::this_thread::sleep_for(std::chrono::seconds(1));
	dprintf(2, "end of ALL\n");
}

int main(int ac, char **av)
{
	try {
		run();
	}
	catch (...) {
	}
}
