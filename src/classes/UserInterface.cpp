/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "UserInterface.hpp"

Plazza::UserInterface::UserInterface(
	Plazza::SlavePool &pool, Plazza::WorkerOutputHandler &output)
	: _pool(pool), _output(output), _launched(false), _hasToStop(false)
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
	dprintf(2, "[UI] Thread started\n");
	_srv = WebServer("127.0.0.1", 8181,
		std::bind(&Plazza::UserInterface::_router, this,
			std::placeholders::_1, std::placeholders::_2));
	dprintf(2, "[UI] Starting at http://127.0.0.1:8181/\n");
	_srv.launch(_hasToStop);
	dprintf(2, "[UI] Stopped\n");
}

std::string Plazza::UserInterface::_router(
	const std::string &method, const std::string &path)
{
	_lastRes = "{ \"method\": \"" + method + "\", \"path\": \"" + path +
		"\" }";
	_endpointHome(method, path);
	_endpointLog(method, path);
	_endpointScrap(method, path);
	_endpointSlaves(method, path);
	return _lastRes;
}

void Plazza::UserInterface::_endpointHome(
	const std::string &, const std::string &path)
{
	std::cmatch cm;
	std::fstream fs;

	if (std::regex_search(path.c_str(), cm, std::regex("^/$"))) {
		fs.open(_homePath, std::fstream::in);
		if (!fs.is_open())
			return;
		_lastRes = "";
		std::string temp;
		while (std::getline(fs, temp))
			_lastRes += temp;
	}
	fs.close();
}

void Plazza::UserInterface::_endpointLog(
	const std::string &, const std::string &path)
{
	std::cmatch cm;
	std::fstream fs;

	if (std::regex_search(path.c_str(), cm, std::regex("^/log/?$"))) {
		if (!_output.hasLogPending()) {
			_lastRes = "{\"error\": \"no log is pending\"}";
			return;
		}
		_lastRes = "{\"result\": \"" + _output.getLogLine() + "\"}";
		_output.popLogLine();
	}
}

void Plazza::UserInterface::_endpointSlaves(
	const std::string &, const std::string &path)
{
	std::cmatch cm;

	if (std::regex_search(path.c_str(), cm, std::regex("^/slaves/?$"))) {
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
