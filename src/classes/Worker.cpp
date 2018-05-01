/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Worker.hpp"
#include <unistd.h>

#include "Scrapper.hpp"

Plazza::Worker::Worker() : _tasks(), _isWorking(false), _isRunning(false)
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
	return _tasks.size();
}

bool Plazza::Worker::isWorking()
{
	return _isWorking;
}

bool Plazza::Worker::isRunning()
{
	return _isRunning;
}

void Plazza::Worker::pushTask(const Plazza::Task &task)
{
	_isWorking = true;
	_tasks.push(task);
	if (!_isRunning) {
		join();
		_isRunning = true;
		_thread = std::thread(&Plazza::Worker::_run, this);
	}
	_threadCond.notify_one();
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
	printf("[WORKER] Thread started\n");
	while (1) {
		if (_tasks.empty()) {
			_isWorking = false;
			std::mutex m;
			std::unique_lock<std::mutex> lk(m);
			_threadCond.wait(lk);
		}
		if (_tasks.empty())
			continue;
		auto task = _tasks.front();
		if (task.getType() == Plazza::Task::Type::EXIT)
			break;
		_parse(task);
		_tasks.pop();
	}
	printf("[WORKER] Thread finished\n");
}

void Plazza::Worker::_parse(Plazza::Task &task)
{
	printf("[WORKER] Thread is working\n");
	Plazza::Scrapper s(task);
	s.startScrapper();
	printf("[WORKER] Thread is not working anymore\n");
}
