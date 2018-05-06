/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "UserInterface.hpp"

Plazza::UserInterface::UserInterface()
	: _launched(false), _hasToStop(false), _pool(nullptr), _output(nullptr)
{
}

Plazza::UserInterface::~UserInterface()
{
	_pool.release();
	_output.release();
	Plazza::UserInterface::stop();
}

void Plazza::UserInterface::launch(
	Plazza::SlavePool &pool, Plazza::WorkerOutputHandler &output)
{
	_pool.reset(&pool);
	_output.reset(&output);
	if (!_launched)
		_thread = std::thread(&Plazza::UserInterface::_run, this);
	_launched = true;
	_hasToStop = false;
}

void Plazza::UserInterface::stop()
{
	_hasToStop = true;
	if (_thread.joinable())
		_thread.join();
	_launched = false;
}

void Plazza::UserInterface::_run()
{
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
	_endpointState(method, path);
	_endpointTask(method, path);
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
			_lastRes += temp + '\n';
	}
	fs.close();
}

void Plazza::UserInterface::_endpointLog(
	const std::string &, const std::string &path)
{
	std::cmatch cm;
	std::fstream fs;

	if (std::regex_search(path.c_str(), cm, std::regex("^/log/?$"))) {
		if (!_output->hasLogPending()) {
			_lastRes = "{\"error\": \"no log is pending\"}";
			return;
		}
		_lastRes = "{\"result\": \"" + _output->getLogLine() + "\"}";
		_output->popLogLine();
	}
}

void Plazza::UserInterface::_endpointState(
	const std::string &, const std::string &path)
{
	std::cmatch cm;

	if (std::regex_search(path.c_str(), cm, std::regex("^/state/?$"))) {
		_lastRes = "{";
		std::vector<std::vector<size_t>> r = _pool->getSummaryLoad();
		for (size_t sl = 0; sl < r.size(); ++sl) {
			_lastRes += "\"" + std::to_string(sl) + "\": {";
			for (size_t wo = 0; wo < r[sl].size(); ++wo)
				_lastRes += "\"" + std::to_string(wo) +
					"\": " + std::to_string(r[sl][wo]) +
					",";
			_lastRes.back() = '}';
			if (sl + 1 != r.size())
				_lastRes += ",";
		}
		_lastRes += "}";
	}
}

void Plazza::UserInterface::_endpointTask(
	const std::string &, const std::string &path)
{
	std::cmatch cm;

	if (std::regex_search(path.c_str(), cm, std::regex("^/task/?$"))) {
		_lastRes = "{";
		std::vector<std::vector<Plazza::Task>> r =
			_pool->getSummaryTask();
		for (size_t sl = 0; sl < r.size(); ++sl) {
			_lastRes += "\"" + std::to_string(sl) + "\": {";
			for (size_t wo = 0; wo < r[sl].size(); ++wo)
				_lastRes += "\"" + std::to_string(wo) +
					"\": { \"file\": \"" +
					r[sl][wo].getFile() +
					"\", \"criteria\": \"" +
					r[sl][wo].getStringifiedCriteria() +
					"\"},";
			_lastRes.back() = '}';
			if (sl + 1 != r.size())
				_lastRes += ",";
		}
		_lastRes += "}";
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
		_pool->pushTask(task);
		_lastRes = "{ \"result\": \"scrap task pushed to workers\", "
			   "\"criteria\": \"" +
			cm[1].str() + "\", \"filename\": \"" + cm[2].str() +
			"\" }";
	}
}
