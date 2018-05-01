/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "SlavePool.hpp"
#include "WebServer.hpp"
#include "socket/ServerTCPSocket.hpp"
#include <regex>
#include <string.h>
#include <thread>
#include <vector>

namespace Plazza {
	class UserInterface {
	public:
		UserInterface(Plazza::SlavePool &);
		~UserInterface();

		void launch();
		void stop();

	protected:
	private:
		void _run();
		std::string _router(const std::string &, const std::string &);
		void _endpointPushTask(
			const std::string &, const std::string &);
		std::map<std::string, Plazza::Task::Criteria> _criteriaRefs{
			{"PHONE_NUMBER", Plazza::Task::Criteria::PHONE_NUMBER},
			{"IP_ADDRESS", Plazza::Task::Criteria::IP_ADDRESS},
			{"EMAIL_ADDRESS",
				Plazza::Task::Criteria::EMAIL_ADDRESS}};

		Plazza::SlavePool &_pool;
		bool _launched;
		bool _hasToStop;
		std::thread _thread;
		WebServer _srv;
		std::string _lastRes;
	};
};
