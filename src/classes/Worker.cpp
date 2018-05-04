/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Worker.hpp"
#include <unistd.h>

#include "Scrapper.hpp"

Plazza::Worker::Worker(
	size_t slaveID, size_t workerID, const std::string &loggerName)
	: _slaveID(slaveID), _workerID(workerID), _tasks(), _isWorking(false),
	  _isRunning(false), _loggerName(loggerName)
{
}

Plazza::Worker::~Worker()
{
	pushTask(Plazza::Task(Plazza::Task::Type::EXIT, "",
		Plazza::Task::Criteria::IP_ADDRESS));
	join();
}

unsigned Plazza::Worker::getLoad()
{
	return _tasks.size() + _isWorking;
}

bool Plazza::Worker::isWorking()
{
	return _isWorking;
}

bool Plazza::Worker::isRunning()
{
	return _isRunning;
}

void Plazza::Worker::pushTask(const Plazza::Task task)
{
	_mutex.lock();
	_tasks.push(task);
	_threadCond.notify_one();
	_mutex.unlock();
	if (!_isRunning) {
		join();
		_isRunning = true;
		_thread = std::thread(&Plazza::Worker::_run, this);
	}
}

void Plazza::Worker::join()
{
	if (_thread.joinable()) {
		_thread.join();
		_isRunning = false;
	}
}

void Plazza::Worker::_run()
{
	printf("[WORKER %lu:%lu] Thread started\n", _slaveID, _workerID);
	_logger = ClientUnixSocket(_loggerName);
	dprintf(1, "[WORKER %lu:%lu] Logging to %s\n", _slaveID, _workerID,
		_loggerName.c_str());
	while (1) {
		_mutex.lock();
		if (_tasks.empty()) {
			std::unique_lock<std::mutex> lk(
				_mutex, std::defer_lock);
			_threadCond.wait(lk);
		}
		if (_tasks.empty())
			continue;
		auto task = _tasks.front();
		_tasks.pop();
		_isWorking = true;
		_mutex.unlock();
		if (task.getType() == Plazza::Task::Type::EXIT)
			break;
		_parse(task);
		_isWorking = false;
	}
	printf("[WORKER %lu:%lu] Thread finished\n", _slaveID, _workerID);
}

void Plazza::Worker::_parse(Plazza::Task &task)
{
	printf("[WORKER %lu:%lu] Thread is working\n", _slaveID, _workerID);
	Plazza::Scrapper s(task, _logger);
	s.startScrapper();
	printf("[WORKER %lu:%lu] Thread is not working anymore\n", _slaveID,
		_workerID);
}
