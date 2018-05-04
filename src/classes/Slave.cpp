/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "Slave.hpp"
#include <functional>
#include <map>
#include <signal.h>
#include <sstream>

Plazza::Slave::Slave(size_t id, unsigned workerCount,
	const std::string &loggerName, const std::function<void(void)> &atFork)
	: _id(id), _pool(_id, workerCount, loggerName), _fork(),
	  _loggerName(loggerName), _atFork(atFork)
{
}

Plazza::Slave::~Slave()
{
	_fork.wait();
}

void Plazza::Slave::launchChild()
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
	_atFork();
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
		}
		catch (...) {
			dprintf(2, "__EXXIT__\n");
			std::exit(0);
		}
	}
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
	return 0;
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
	return 0;
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
	return 0;
}

void Plazza::Slave::exit()
{
	if (_fork.isChild()) {
		_pool.exit();
		dprintf(2, "__EXIIT__\n");
		// std::this_thread::sleep_for(std::chrono::seconds(5));
		// dprintf(2, "fils: pid: %d %d\n", getpid(), _fork.getPid());
		::exit(0);
	}
	else {
		dprintf(2, "perr: pid: %d %d\n", getpid(), _fork.getPid());
		dprintf(2, "SENDED EXIT TO FORK\n");
		_fork.getSocket().send("EXIT\n");
		dprintf(2, "SENDED WAIT TO FORK\n");
		std::this_thread::sleep_for(std::chrono::seconds(2));
		_fork.wait();
		dprintf(2, "WAITED TO FORK\n");
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
