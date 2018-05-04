/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** WorkerPool
*/

#include "WorkerPool.hpp"
#include <algorithm>

Plazza::WorkerPool::WorkerPool(
	size_t id, size_t threadCount, const std::string &loggerName)
	: _id(id), _threadCount(threadCount), _loggerName(loggerName)
{
	_workers.reserve(_threadCount);
	for (size_t i = 0; i < _threadCount; i++)
		_workers.push_back(
			std::make_unique<Plazza::Worker>(_id, i, loggerName));
}

Plazza::WorkerPool::~WorkerPool()
{
}

unsigned Plazza::WorkerPool::getLoad()
{
	unsigned load = 0;

	for (auto &w : _workers)
		load += w->getLoad();
	return load;
}

Plazza::Worker &Plazza::WorkerPool::getBestWorker()
{
	unsigned minWorker = 0;
	unsigned minLoad = _workers[0]->getLoad();

	for (unsigned i = 0; i < _workers.size(); ++i)
		if (_workers[i]->getLoad() < minLoad) {
			minWorker = i;
			minLoad = _workers[i]->getLoad();
		}
	printf("[WorkerPool] Using worker %d (with load %d)\n", minWorker,
		minLoad);
	return *_workers[minWorker].get();
}

void Plazza::WorkerPool::pushTask(const Plazza::Task task)
{
	printf("[WorkerPool] Available power %d\n", getAvailablePower());
	getBestWorker().pushTask(task);
}

unsigned Plazza::WorkerPool::getTotalPower()
{
	return _workers.size();
}

unsigned Plazza::WorkerPool::getAvailablePower()
{
	unsigned availablePower = 0;

	for (auto &w : _workers)
		availablePower += !w->isWorking();
	return availablePower;
}

void Plazza::WorkerPool::exit()
{
	std::for_each(_workers.begin(), _workers.end(),
		[](std::unique_ptr<Plazza::Worker> &worker) {
			worker->pushTask(Plazza::Task());
		});
	_workers.clear();
}
