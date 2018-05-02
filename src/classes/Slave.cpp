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
	std::map<std::string,
		void (Plazza::Slave::*)(std::istringstream & input)>
		map{{"LOAD", &Plazza::Slave::handleLoad},
			{"TOTAL", &Plazza::Slave::handleTotalPower},
			{"AVAILABLE", &Plazza::Slave::handleAvailablePower},
			{"EXIT", &Plazza::Slave::handleExit},
			{"TASK", &Plazza::Slave::handleTask}};

	if (_fork.isChild() == 0)
		return;
	auto socket = _fork.getSocket();
	while (1) {
		try {
			auto line = socket.receive();
			auto order = std::istringstream(line);
			std::string opcode;
			order >> opcode;
			// std::cout << "GOT OPCODE: '" << opcode << "'"
			// 	  << std::endl;
			(this->*map.at(opcode))(order);
		} catch (...) {
			std::exit(0);
		}
	}
}

Plazza::Slave::~Slave()
{
	_fork.wait();
}

unsigned Plazza::Slave::getLoad()
{
	if (_fork.isChild())
		_fork.getSocket().send(std::to_string(_pool.getLoad()) + "\n");
	else {
		_fork.getSocket().send("LOAD\n");
		auto ret = std::strtoul(
			_fork.getSocket().receive().c_str(), 0, 10);
		// std::cout << "|=> " << ret << std::endl;
		return ret;
	}
}

void Plazza::Slave::pushTask(const Plazza::Task task)
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
		auto ret = std::strtoul(
			_fork.getSocket().receive().c_str(), 0, 10);
		// std::cout << "|=> " << ret << std::endl;
		return ret;
	}
}

unsigned Plazza::Slave::getAvailablePower()
{
	if (_fork.isChild())
		_fork.getSocket().send(
			std::to_string(_pool.getAvailablePower()) + "\n");
	else {
		_fork.getSocket().send("AVAILABLE\n");
		auto ret = std::strtoul(
			_fork.getSocket().receive().c_str(), 0, 10);
		// std::cout << "|=> " << ret << std::endl;
		return ret;
	}
}

void Plazza::Slave::exit()
{
	if (_fork.isChild())
		_pool.exit();
	else {
		_fork.getSocket().send("EXIT\n");
		_fork.wait();
	}
}

void Plazza::Slave::handleTask(std::istringstream &input)
{
	Plazza::Task task;
	input >> task;
	Plazza::Slave::pushTask(task);
}

void Plazza::Slave::handleLoad(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::getLoad();
}

void Plazza::Slave::handleTotalPower(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::getTotalPower();
}

void Plazza::Slave::handleAvailablePower(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::getAvailablePower();
}

void Plazza::Slave::handleExit(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::exit();
}