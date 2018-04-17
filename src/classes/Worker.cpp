/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Worker.hpp"

Plazza::Worker::Worker()
	: _tasks()
	, _isWorking(false)
	, _isRunning(false)
{}

Plazza::Worker::~Worker()
{
	pushTask(Plazza::Task(Plazza::Task::EXIT));
	join();
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
	std::cout << "Thread started" << std::endl;

	while (1) {
		if (_tasks.empty()) {
			std::mutex m;
			std::unique_lock<std::mutex> lk(m);
			_threadCond.wait(lk);
		}
		if (_tasks.empty())
			continue ;
		auto task = _tasks.front();
		if (task.getType() == Plazza::Task::Type::EXIT)
			break ;
		_tasks.pop();
		_isWorking = true;
		_parse();
		_isWorking = false;
	}

	std::cout << "Thread finished" << std::endl;
}

void Plazza::Worker::_parse()
{
	std::cout << "Thread is working" << std::endl;
	std::cout << "Thread is not working anymore" << std::endl;
}
