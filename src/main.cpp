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
#include "classes/Worker.hpp"
#include "classes/socket/ClientTCPSocket.hpp"
#include "classes/socket/ClientUnixSocket.hpp"
#include "classes/UserInterface.hpp"
#include "classes/WorkerOutputHandler.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main(int ac, char **av)
{
	// TEST PARSER AND WORKERS
	// Plazza::Parser p;
	Plazza::SlavePool pool(1);
	// bool hasTasks = true;

	// while (hasTasks) {
	// 	auto task = p.getNextTask();
	// 	std::cout << task << std::endl;
	// 	pool.pushTask(task);
	// 	hasTasks = !(task.getType() == Plazza::Task::Type::EXIT);
	// }

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

	Plazza::UserInterface ui(pool);
	ui.launch();
	std::this_thread::sleep_for(std::chrono::seconds(100));
	ui.stop();

	// Plazza::WorkerOutputHandler w;
	// printf("%s\n", w.getPath().c_str());
	// ClientUnixSocket u(w.getPath());
	// u.send("oui!\n");
	// std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}
