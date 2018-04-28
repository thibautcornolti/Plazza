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
#include "classes/socket/ClientTCPSocket.hpp"

int main(int ac, char **av)
{
	// Plazza::Parser p;
	// Plazza::SlavePool pool(1);
	// bool hasTasks = true;
	ClientTCPSocket socket("hirevo.eu", 4444);

	if (ac != 2)
		return 84;
	std::cout << socket.receive() << std::endl;
	socket.send("user anonymous\r\n");
	std::cout << socket.receive() << std::endl;
	socket.close();
	// while (hasTasks) {
	// 	auto task = p.getNextTask();
	// 	std::cout << task << std::endl;
	// 	pool.pushTask(task);
	// 	hasTasks = !(task.getType() == Plazza::Task::Type::EXIT);
	// }
	return 0;
}
