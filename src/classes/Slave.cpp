/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "Slave.hpp"
#include <functional>
#include <map>
#include <sstream>

Plazza::Slave::Slave(unsigned workerCount) : _pool(workerCount), _fork()
{
	if (_fork.isChild() == 0)
		return;
	while (1) {
		auto socket = _fork.getSocket();
		socket.waitData(-1);
		if (socket.isDataPending()) {
			auto order = std::istringstream(socket.receive());
			std::string opcode;
			std::string remaining;
			order >> opcode;
			std::cout << "GOT OPCODE: '" << opcode << "'"
				  << std::endl;
			if (opcode == "LOAD")
				Plazza::Slave::getLoad();
			else if (opcode == "TOTAL")
				Plazza::Slave::getTotalPower();
			else if (opcode == "AVAILABLE")
				Plazza::Slave::getAvailablePower();
			else if (opcode == "TASK") {
				Plazza::Task task;
				order >> task;
				Plazza::Slave::pushTask(task);
			}
		}
	}
}

Plazza::Slave::~Slave()
{
}

unsigned Plazza::Slave::getLoad()
{
	if (_fork.isChild())
		_fork.getSocket().send(std::to_string(_pool.getLoad()) + "\n");
	else {
		_fork.getSocket().send("LOAD\n");
		return std::strtoul(
			_fork.getSocket().receive().c_str(), 0, 10);
	}
}

void Plazza::Slave::pushTask(Plazza::Task &task)
{
	if (_fork.isChild())
		_pool.pushTask(task);
	else {
		std::ostringstream oss;
		oss << "TASK " << task << "\n";
		_fork.getSocket().send(oss.str());
	}
}

unsigned Plazza::Slave::getTotalPower()
{
	if (_fork.isChild())
		_fork.getSocket().send(
			std::to_string(_pool.getTotalPower()) + "\n");
	else {
		_fork.getSocket().send("TOTAL\n");
		return std::strtoul(
			_fork.getSocket().receive().c_str(), 0, 10);
	}
}

unsigned Plazza::Slave::getAvailablePower()
{
	if (_fork.isChild())
		_fork.getSocket().send(
			std::to_string(_pool.getAvailablePower()) + "\n");
	else {
		_fork.getSocket().send("AVAILABLE\n");
		return std::strtoul(
			_fork.getSocket().receive().c_str(), 0, 10);
	}
}
