/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Worker.hpp"
#include <unistd.h>

#include "Scrapper.hpp"

Plazza::Worker::Worker(const std::string &loggerName)
	: _tasks(), _isWorking(false), _isRunning(false),
	  _loggerName(loggerName)
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
		dprintf(2, "Joining\n");
		_thread.join();
		dprintf(2, "Joined\n");
		_isRunning = false;
	}
}

void Plazza::Worker::_run()
{
	dprintf(2, "[WORKER] Thread started\n");
	_logger = ClientUnixSocket(_loggerName);
	dprintf(2, "[WORKER] Logging to %s\n", _loggerName.c_str());
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
	dprintf(2, "[WORKER] Thread finished\n");
}

void Plazza::Worker::_parse(Plazza::Task &task)
{
	dprintf(2, "[WORKER] Thread is working\n");
	Plazza::Scrapper s(task, _logger);
	s.startScrapper();
	dprintf(2, "[WORKER] Thread is not working anymore\n");
}
