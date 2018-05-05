/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "Slave.hpp"
#include <functional>
#include <map>
#include <regex>
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
			{"SUMMARY_L", &Plazza::Slave::handleSummaryLoad},
			{"SUMMARY_T", &Plazza::Slave::handleSummaryTask},
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

std::vector<size_t> Plazza::Slave::getSummaryLoad()
{
	std::vector<size_t> res;

	if (_fork.isChild()) {
		std::string s = "";
		for (auto &l : _pool.getSummaryLoad()) {
			s += std::to_string(l);
			s += ',';
		}
		s.back() = '\n';
		_fork.getSocket().send(s);
	}
	else {
		_fork.getSocket().send("SUMMARY_L\n");
		std::string rec = _fork.getSocket().receive();
		std::cmatch cm;
		size_t offset = 0;
		while (offset < rec.size() &&
			std::regex_search(rec.c_str() + offset, cm,
				std::regex("[0-9]+"))) {
			res.push_back(
				std::strtoul(cm[0].str().c_str(), 0, 10));
			offset += cm[0].length() + 1;
		}
		dprintf(2, "load: %s\n", rec.c_str());
	}
	return res;
}

std::vector<Plazza::Task> Plazza::Slave::getSummaryTask()
{
	std::vector<Plazza::Task> res;

	if (_fork.isChild()) {
		std::string s = "";
		for (auto &l : _pool.getSummaryTask()) {
			std::stringstream ss("");
			ss << l;
			s += ss.str();
			s += ',';
		}
		s.back() = '\n';
		_fork.getSocket().send(s);
	}
	else {
		_fork.getSocket().send("SUMMARY_T\n");
		std::string rec = _fork.getSocket().receive();
		std::cmatch cm;
		size_t offset = 0;
		while (offset < rec.size() &&
			std::regex_search(rec.c_str() + offset, cm,
				std::regex("<Task.*?>"))) {
			Plazza::Task t;
			std::stringstream ss(cm[0]);
			ss >> t;
			res.push_back(t);
			offset += cm[0].length() + 1;
		}
		dprintf(2, "load: %s\n", rec.c_str());
	}
	return res;
}

void Plazza::Slave::exit()
{
	if (_fork.isChild()) {
		_pool.exit();
		::exit(0);
	}
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

void Plazza::Slave::handleSummaryLoad(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::getSummaryLoad();
}

void Plazza::Slave::handleSummaryTask(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::getSummaryTask();
}

void Plazza::Slave::handleExit(std::istringstream &input)
{
	static_cast<void>(input);
	Plazza::Slave::exit();
}
