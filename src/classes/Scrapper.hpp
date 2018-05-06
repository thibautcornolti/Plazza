//
// EPITECH PROJECT, 2018
// Scrapper.hpp
// File description:
// Scrapper.hpp
//

#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>

#include "Task.hpp"
#include "socket/ClientUnixSocket.hpp"

namespace Plazza {
	class Scrapper {
	public:
		Scrapper(Task &, ClientUnixSocket &);
		~Scrapper();

		void startScrapper();

	protected:
	private:
		Task _task;
		ClientUnixSocket _logger;
		Plazza::Task::Type _type;
		Plazza::Task::Criteria _criteria;
		std::string _file;
		std::map<Task::Criteria, std::regex> _criteriaRegs = {
			{Task::Criteria::EMAIL_ADDRESS,
				std::regex("[a-zA-Z0-9_\\.-]+@[a-zA-Z0-9_\\.-]"
					   "+\\.[a-zA-Z0-9_\\.-]+")},
			{Task::Criteria::PHONE_NUMBER,
				std::regex("([0-9]{2}(\\.| )?){4}[0-9]{1,2}")},
			{Task::Criteria::IP_ADDRESS,
				std::regex("(?:\\s|^)((?:[0-9]{1,3}\\.){3}[0-"
					   "9]{1,3})(?:\\s|$)")}};
	};
}
