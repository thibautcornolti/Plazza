/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "UserInterface.hpp"

Plazza::UserInterface::UserInterface(Plazza::SlavePool &pool)
	: _pool(pool), _launched(false), _hasToStop(false)
{
}

Plazza::UserInterface::~UserInterface()
{
	Plazza::UserInterface::stop();
}

void Plazza::UserInterface::launch()
{
	if (!_launched)
		_thread = std::thread(&Plazza::UserInterface::_run, this);
	_launched = true;
	_hasToStop = false;
}

void Plazza::UserInterface::stop()
{
	_hasToStop = true;
	_thread.join();
	_launched = false;
}

void Plazza::UserInterface::_run()
{
	printf("[UI] Thread started\n");
	_srv = WebServer("127.0.0.1", 8181,
		std::bind(&Plazza::UserInterface::_router, this,
			std::placeholders::_1, std::placeholders::_2));
	printf("[UI] Starting at http://127.0.0.1:8181/\n");
	_srv.launch(_hasToStop);
	printf("[UI] Stopped\n");
}

std::string Plazza::UserInterface::_router(
	const std::string &method, const std::string &path)
{
	_lastRes = "{ \"method\": \"" + method + "\", \"path\": \"" + path +
		"\" }";
	_endpointScrap(method, path);
	_endpointSlaves(method, path);
	return _lastRes;
}

void Plazza::UserInterface::_endpointSlaves(
	const std::string &, const std::string &path)
{
	std::cmatch cm;

	if (std::regex_search(path.c_str(), cm, std::regex("^/slaves/$"))) {
	}
}

void Plazza::UserInterface::_endpointScrap(
	const std::string &, const std::string &path)
{
	std::cmatch cm;

	if (std::regex_search(path.c_str(), cm,
		    std::regex("^/scrap/"
			       "(IP_ADDRESS|PHONE_NUMBER|EMAIL_ADDRESS)/([^/"
			       "]+)/?$"))) {
		Plazza::Task task(Plazza::Task::SCRAP, cm[2].str(),
			_criteriaRefs.at(cm[1].str()));
		_pool.pushTask(task);
		_lastRes = "{ \"result\": \"scrap task pushed to workers\", "
			   "\"criteria\": \"" +
			cm[1].str() + "\", \"filename\": \"" + cm[2].str() +
			"\" }";
	}
}
