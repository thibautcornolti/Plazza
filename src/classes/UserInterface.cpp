/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "UserInterface.hpp"

Plazza::UserInterface::UserInterface()
{
}

Plazza::UserInterface::~UserInterface()
{
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
}

void Plazza::UserInterface::_run()
{
	printf("[UI] Thread started\n");
	_srv = WebServer("127.0.0.1", 8181,
		std::bind(&Plazza::UserInterface::_router, this,
			std::placeholders::_1, std::placeholders::_2));
	printf("[UI] Starting at http://127.0.0.1:8181/\n");
	_srv.launch();
}

std::string Plazza::UserInterface::_router(
	const std::string &method, const std::string &path)
{
	return method + " " + path;
}
