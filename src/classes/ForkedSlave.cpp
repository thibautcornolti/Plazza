/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "ForkedSlave.hpp"

Plazza::ForkedSlave::ForkedSlave(unsigned workerCount)
	: _workerCount(workerCount), _workers(workerCount)
{
}

Plazza::ForkedSlave::~ForkedSlave()
{
}

unsigned Plazza::ForkedSlave::getLoad()
{
	unsigned load = 0;

	for (auto &w : _workers)
		load += w.getLoad();
	return load;
}

Plazza::Worker &Plazza::ForkedSlave::getBestWorker()
{
	unsigned minWorker = 0;
	unsigned minLoad = _workers[0].getLoad();

	for (unsigned i = 0; i < _workers.size(); ++i)
		if (_workers[i].getLoad() < minLoad) {
			minWorker = i;
			minLoad = _workers[i].getLoad();
		}
	printf("[ForkedSlave] Using worker %d (with load %d)\n", minWorker, minLoad);
	return _workers[minWorker];
}

void Plazza::ForkedSlave::pushTask(Plazza::Task &task)
{
	printf("[ForkedSlave] Available power %d\n", getAvailablePower());
	getBestWorker().pushTask(task);
}

unsigned Plazza::ForkedSlave::getTotalPower()
{
	return _workers.size();
}

unsigned Plazza::ForkedSlave::getAvailablePower()
{
	unsigned availablePower = 0;

	for (auto &w : _workers)
		availablePower += !w.isWorking();
	return availablePower;
}
