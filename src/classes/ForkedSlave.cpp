/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "ForkedSlave.hpp"

Plazza::ForkedSlave::ForkedSlave(unsigned workerCount)
	: _workerCount(workerCount), _pool(workerCount)
{
}

Plazza::ForkedSlave::~ForkedSlave()
{
}

unsigned Plazza::ForkedSlave::getLoad()
{
	return _pool.getLoad();
}

void Plazza::ForkedSlave::pushTask(Plazza::Task &task)
{
	printf("[ForkedSlave] Available power %d\n", getAvailablePower());
	_pool.pushTask(task);
}

unsigned Plazza::ForkedSlave::getTotalPower()
{
	return _pool.getTotalPower();
}

unsigned Plazza::ForkedSlave::getAvailablePower()
{
	return _pool.getAvailablePower();
}
