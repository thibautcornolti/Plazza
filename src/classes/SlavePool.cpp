/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "SlavePool.hpp"
#include <algorithm>

Plazza::SlavePool::SlavePool(unsigned workerCount,
	const std::string &loggerName, const std::function<void(void)> &atFork)
	: _socket(), _workerCount(workerCount), _slaves(),
	  _loggerName(loggerName), _atFork(atFork)
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
	dprintf(2, "[SLAVE POOL] Using slave %d (with load %d)\n", minSlave,
		minLoad);
	return *_slaves[minSlave];
}

void Plazza::SlavePool::createSlave()
{
	_slaves.push_back(std::make_unique<Plazza::Slave>(
		_slaves.size(), _workerCount, _loggerName, _atFork));
	_slaves.back()->launchChild();
}

void Plazza::SlavePool::pushTask(Plazza::Task task)
{
	dprintf(2, "[SLAVE POOL] Available power %d\n", getAvailablePower());
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

void Plazza::SlavePool::exit()
{
	int i = 0;
	std::for_each(_slaves.begin(), _slaves.end(),
		[&i](std::unique_ptr<Plazza::Slave> &slave) {
			dprintf(2, "[SlavePool] EXIT pushed to Slave %d\n", i);
			slave->exit();
			i += 1;
		});
	_slaves.clear();
}
