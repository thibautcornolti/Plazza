/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "Slave.hpp"

Plazza::Slave::Slave(unsigned workerCount) : _pool(workerCount), _fork()
{
}

Plazza::Slave::~Slave()
{
}

unsigned Plazza::Slave::getLoad()
{
	return _pool.getLoad();
}

void Plazza::Slave::pushTask(Plazza::Task &task)
{
	_pool.pushTask(task);
}

unsigned Plazza::Slave::getTotalPower()
{
	return _pool.getTotalPower();
}

unsigned Plazza::Slave::getAvailablePower()
{
	return _pool.getAvailablePower();
}
