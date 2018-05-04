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

bool Plazza::Worker::isRunning() const
{
	return _isRunning;
}

void Plazza::Worker::pushTask(const Plazza::Task task)
{
	if (!_isRunning && task.getType() == Plazza::Task::EXIT)
		return;
	_mutex.lock();
	_tasks.push(task);
	_threadCond.notify_one();
	_mutex.unlock();
	if (!_isRunning) {
		_isRunning = true;
		_thread = std::thread(&Plazza::Worker::_run, this);
	}
}

void Plazza::Worker::join()
{
	dprintf(2, "[WORKER %lu:%lu] Try to join\n", _slaveID, _workerID);
	while (_thread.joinable()) {
		dprintf(2, "[WORKER %lu:%lu] Joining\n", _slaveID, _workerID);
		_thread.join();
		dprintf(2, "[WORKER %lu:%lu] Joined\n", _slaveID, _workerID);
		_isRunning = false;
	}
}

void Plazza::Worker::_run()
{
	dprintf(2, "[WORKER %lu:%lu] Thread started\n", _slaveID, _workerID);
	_logger = ClientUnixSocket(_loggerName);
	dprintf(2, "[WORKER %lu:%lu] Logging to %s\n", _slaveID, _workerID,
		_loggerName.c_str());
	while (1) {
		if (_tasks.empty()) {
			std::unique_lock<std::mutex> lk(
				_mutex, std::defer_lock);
			_threadCond.wait(lk);
		}
		if (_tasks.empty()) {
			continue;
		}
		// _mutex.lock();
		auto task = _tasks.front();
		_tasks.pop();
		// _mutex.unlock();
		_isWorking = true;
		if (task.getType() == Plazza::Task::Type::EXIT)
			break;
		_parse(task);
		_isWorking = false;
	}
	_isWorking = false;
	_logger.close();
	dprintf(2, "[WORKER %lu:%lu] Thread finished\n", _slaveID, _workerID);
}

void Plazza::Worker::_parse(Plazza::Task &task)
{
	dprintf(2, "[WORKER %lu:%lu] Thread is working\n", _slaveID,
		_workerID);
	Plazza::Scrapper s(task, _logger);
	s.startScrapper();
	dprintf(2, "[WORKER %lu:%lu] Thread is not working anymore\n",
		_slaveID, _workerID);
}
