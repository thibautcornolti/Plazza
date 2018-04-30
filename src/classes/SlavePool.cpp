/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "SlavePool.hpp"

Plazza::SlavePool::SlavePool(unsigned workerCount)
	: _socket(), _workerCount(workerCount), _slaves()
{
}

Plazza::SlavePool::~SlavePool()
{
}

Plazza::Slave &Plazza::SlavePool::getBestSlave()
{
	unsigned minSlave = 0;
	unsigned minLoad = _slaves[0]->getLoad();

	for (unsigned i = 0; i < _slaves.size(); ++i)
		if (_slaves[i]->getLoad() < minLoad) {
			minSlave = i;
			minLoad = _slaves[i]->getLoad();
		}
	printf("[SLAVE POOL] Using slave %d (with load %d)\n", minSlave,
		minLoad);
	return *_slaves[minSlave];
}

void Plazza::SlavePool::createSlave()
{
	_slaves.push_back(std::make_unique<Plazza::Slave>(_workerCount));
}

void Plazza::SlavePool::pushTask(Plazza::Task &task)
{
	printf("[SLAVE POOL] Available power %d\n", getAvailablePower());
	if (getAvailablePower() == 0)
		createSlave();
	getBestSlave().pushTask(task);
}

unsigned Plazza::SlavePool::getTotalPower()
{
	unsigned totalPower = 0;

	for (auto &s : _slaves)
		totalPower += s->getTotalPower();
	return totalPower;
}

unsigned Plazza::SlavePool::getAvailablePower()
{
	unsigned availablePower = 0;

	for (auto &s : _slaves)
		availablePower += s->getAvailablePower();
	return availablePower;
}
