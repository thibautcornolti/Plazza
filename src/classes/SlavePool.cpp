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
	  _loggerName(loggerName), _atFork(atFork), _hasToStop(false)
{
	_timeoutThread =
		std::thread(&Plazza::SlavePool::_timeoutHandler, this);
}

Plazza::SlavePool::~SlavePool()
{
	_hasToStop = true;
	if (_timeoutThread.joinable())
		_timeoutThread.join();
}

std::pair<std::unique_ptr<Plazza::Slave>, std::time_t> &
Plazza::SlavePool::getBestSlave()
{
	unsigned minSlave = 0;
	unsigned minLoad = std::get<0>(_slaves[0])->getLoad();

	for (unsigned i = 0; i < _slaves.size(); ++i)
		if (std::get<0>(_slaves[i])->getLoad() < minLoad) {
			minSlave = i;
			minLoad = std::get<0>(_slaves[i])->getLoad();
		}
	return _slaves[minSlave];
}

void Plazza::SlavePool::createSlave()
{
	_slaves.push_back(
		std::make_pair(std::make_unique<Plazza::Slave>(_slaves.size(),
				       _workerCount, _loggerName, _atFork),
			std::time(nullptr)));
	std::get<0>(_slaves.back())->launchChild();
}

void Plazza::SlavePool::pushTask(Plazza::Task task)
{
	if (getLoad() >= 2 * _workerCount * _slaves.size())
		createSlave();
	auto &bestSlave = getBestSlave();
	std::get<0>(bestSlave)->pushTask(task);
	std::get<1>(bestSlave) = std::time(nullptr);
}

unsigned Plazza::SlavePool::getLoad()
{
	unsigned load = 0;

	for (auto &s : _slaves)
		load += std::get<0>(s)->getLoad();
	return load;
}

std::vector<std::vector<size_t>> Plazza::SlavePool::getSummaryLoad()
{
	std::vector<std::vector<size_t>> res;

	res.reserve(_slaves.size());
	for (auto &s : _slaves)
		res.emplace_back(std::get<0>(s)->getSummaryLoad());
	return res;
}

std::vector<std::vector<Plazza::Task>> Plazza::SlavePool::getSummaryTask()
{
	std::vector<std::vector<Plazza::Task>> res;

	res.reserve(_slaves.size());
	for (auto &s : _slaves)
		res.emplace_back(std::get<0>(s)->getSummaryTask());
	return res;
}

void Plazza::SlavePool::exit()
{
	int i = 0;
	_hasToStop = true;
	if (_timeoutThread.joinable())
		_timeoutThread.join();
	std::for_each(_slaves.begin(), _slaves.end(),
		[&i](std::pair<std::unique_ptr<Slave>, std::time_t> &slave) {
			std::get<0>(slave)->exit();
			i += 1;
		});
	_slaves.clear();
}

void Plazza::SlavePool::_timeoutHandler()
{
	while (!_hasToStop) {
		auto currentTime = std::time(nullptr);
		for (size_t i = 0; i < _slaves.size(); ++i) {
			if (currentTime - std::get<1>(_slaves[i]) >= 5 &&
				std::get<0>(_slaves[i])->getLoad() == 0) {
				auto b = _slaves.begin();
				std::advance(b, i);
				_slaves.erase(b);
				std::get<0>(_slaves[i])->exit();
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
