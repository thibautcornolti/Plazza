/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Plazza
*/

#include "Slave.hpp"

Plazza::Slave::Slave(unsigned workerCount)
	: _workerCount(workerCount)
	, _workers(workerCount)
{}

Plazza::Slave::~Slave()
{}

unsigned Plazza::Slave::getLoad()
{
	unsigned load = 0;

	for (auto &w : _workers)
		load += w.isWorking();
	return load;
}

Plazza::Worker &Plazza::Slave::getBestWorker()
{
	unsigned minWorker = 0;
	unsigned minLoad = _workers[0].getLoad();

	for (unsigned i = 0 ; i < _workers.size() ; ++i)
		if (_workers[i].getLoad() < minLoad) {
			minWorker = i;
			minLoad = _workers[i].getLoad();
		}
	return _workers[minWorker];
}

void Plazza::Slave::pushTask(Plazza::Task &task)
{
	getBestWorker().pushTask(task);
}
