/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "SlavePool.hpp"

Plazza::SlavePool::SlavePool() : _slaves()
{
}

Plazza::SlavePool::~SlavePool()
{
}

Plazza::Slave &Plazza::SlavePool::getBestSlave()
{
	unsigned minSlave = 0;
	unsigned minLoad = _slaves[0].getLoad();

	for (unsigned i = 0; i < _slaves.size(); ++i)
		if (_slaves[i].getLoad() < minLoad) {
			minSlave = i;
			minLoad = _slaves[i].getLoad();
		}
	return _slaves[minSlave];
}

void Plazza::SlavePool::pushTask(Plazza::Task &task)
{
	getBestSlave().pushTask(task);
}
