/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "WebServer.hpp"
#include "socket/ServerTCPSocket.hpp"
#include <string.h>
#include <thread>
#include <vector>

namespace Plazza {
	class UserInterface {
	public:
		UserInterface();
		~UserInterface();

		void launch();
		void stop();

	protected:
	private:
		void _run();
		std::string _router(const std::string &, const std::string &);

		bool _launched;
		bool _hasToStop;
		std::thread _thread;
		WebServer _srv;
	};
};
