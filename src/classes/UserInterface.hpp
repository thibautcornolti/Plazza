/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <string.h>
#include <vector>
#include <thread>
#include "socket/ServerTCPSocket.hpp"
#include "WebServer.hpp"

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

		bool _launched;
		bool _hasToStop;
		std::thread _thread;
		WebServer _srv;
	};
};
