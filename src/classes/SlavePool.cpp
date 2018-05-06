/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "SlavePool.hpp"

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
	if (getLoad() >= 2 * _workerCount * _slaves.size())
		createSlave();
	getBestSlave().pushTask(task);
}

unsigned Plazza::SlavePool::getLoad()
{
	unsigned load = 0;

	for (auto &s : _slaves)
		load += s->getLoad();
	return load;
}

std::vector<std::vector<size_t>> Plazza::SlavePool::getSummaryLoad()
{
	std::vector<std::vector<size_t>> res;

	res.reserve(_slaves.size());
	for (auto &s : _slaves)
		res.emplace_back(s->getSummaryLoad());
	return res;
}

std::vector<std::vector<Plazza::Task>> Plazza::SlavePool::getSummaryTask()
{
	std::vector<std::vector<Plazza::Task>> res;

	res.reserve(_slaves.size());
	for (auto &s : _slaves)
		res.emplace_back(s->getSummaryTask());
	return res;
}

void Plazza::SlavePool::exit()
{
	int i = 0;
	std::for_each(_slaves.begin(), _slaves.end(),
		[&i](std::unique_ptr<Plazza::Slave> &slave) {
			slave->exit();
			i += 1;
		});
	_slaves.clear();
}
