/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include "SlavePool.hpp"
#include "WebServer.hpp"
#include "WorkerOutputHandler.hpp"
#include "socket/ServerTCPSocket.hpp"
#include <fstream>
#include <regex>
#include <string.h>
#include <string>
#include <memory>
#include <thread>
#include <vector>

namespace Plazza {
	class UserInterface {
	public:
		UserInterface();
		~UserInterface();

		void launch(
			Plazza::SlavePool &, Plazza::WorkerOutputHandler &);
		void stop();

	protected:
	private:
		void _run();
		std::string _router(const std::string &, const std::string &);
		void _endpointHome(const std::string &, const std::string &);
		void _endpointLog(const std::string &, const std::string &);
		void _endpointScrap(const std::string &, const std::string &);
		void _endpointSlaves(const std::string &, const std::string &);
		std::map<std::string, Plazza::Task::Criteria> _criteriaRefs{
			{"PHONE_NUMBER", Plazza::Task::Criteria::PHONE_NUMBER},
			{"IP_ADDRESS", Plazza::Task::Criteria::IP_ADDRESS},
			{"EMAIL_ADDRESS",
				Plazza::Task::Criteria::EMAIL_ADDRESS}};

		std::unique_ptr<Plazza::SlavePool> _pool;
		std::unique_ptr<Plazza::WorkerOutputHandler> _output;
		bool _launched;
		bool _hasToStop;
		std::thread _thread;
		WebServer _srv;
		std::string _lastRes;
		const std::string _homePath = "html/main.html";
	};
};
