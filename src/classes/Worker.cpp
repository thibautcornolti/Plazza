/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Worker.hpp"

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

Plazza::Task Plazza::Worker::getTask()
{
	return _currentTask;
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
	while (_thread.joinable()) {
		_thread.join();
		_isRunning = false;
	}
}

void Plazza::Worker::_run()
{
	_logger = ClientUnixSocket(_loggerName);
	while (1) {
		if (!_waitForTask())
			continue;
		_currentTask = _tasks.front();
		_tasks.pop();
		_mutex.unlock();
		_isWorking = true;
		if (_currentTask.getType() == Plazza::Task::Type::EXIT)
			break;
		_parse(_currentTask);
		_currentTask = Plazza::Task();
		_isWorking = false;
	}
	_isWorking = false;
	_logger.close();
}

bool Plazza::Worker::_waitForTask()
{
	bool res = true;

	_mutex.lock();
	if (_tasks.empty()) {
		std::unique_lock<std::mutex> lk(_mutex, std::defer_lock);
		_threadCond.wait(lk);
	}
	if (_tasks.empty()) {
		_mutex.unlock();
		res = false;
	}
	return res;
}

void Plazza::Worker::_parse(Plazza::Task &task)
{
	Plazza::Scrapper s(task, _logger);
	s.startScrapper();
}
