/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "Slave.hpp"

Plazza::Slave::Slave(unsigned workerCount)
	: _workerCount(workerCount), _workers(workerCount)
{
}

Plazza::Slave::~Slave()
{
}

unsigned Plazza::Slave::getLoad()
{
	unsigned load = 0;

	for (auto &w : _workers)
		load += w.getLoad();
	return load;
}

Plazza::Worker &Plazza::Slave::getBestWorker()
{
	unsigned minWorker = 0;
	unsigned minLoad = _workers[0].getLoad();

	for (unsigned i = 0; i < _workers.size(); ++i)
		if (_workers[i].getLoad() < minLoad) {
			minWorker = i;
			minLoad = _workers[i].getLoad();
		}
	printf("[SLAVE] Using worker %d (with load %d)\n", minWorker, minLoad);
	return _workers[minWorker];
}

void Plazza::Slave::pushTask(Plazza::Task &task)
{
	printf("[SLAVE] Available power %d\n", getAvailablePower());
	getBestWorker().pushTask(task);
}

unsigned Plazza::Slave::getTotalPower()
{
	return _workers.size();
}

unsigned Plazza::Slave::getAvailablePower()
{
	unsigned availablePower = 0;

	for (auto &w : _workers)
		availablePower += !w.isWorking();
	return availablePower;
}
