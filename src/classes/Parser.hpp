/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Parser
*/

#pragma once

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "Task.hpp"

namespace Plazza {
	class Parser {
	public:
		Parser();
		~Parser();

		Plazza::Task getNextTask();

	protected:
	private:
		Plazza::Task parseNextCommand(Plazza::Task, std::string);
		std::map<std::string, Plazza::Task::Criteria> tab{
			{"PHONE_NUMBER", Plazza::Task::Criteria::PHONE_NUMBER},
			{"IP_ADDRESS", Plazza::Task::Criteria::IP_ADDRESS},
			{"EMAIL_ADDRESS",
				Plazza::Task::Criteria::EMAIL_ADDRESS}};
		std::vector<std::string> split(
			const std::string &in, const std::string &pattern);
		std::string capture(
			const std::string &in, const std::string &pattern);
		std::string replace(const std::string &in,
			const std::string &pattern,
			const std::string &pholder);
		static const std::regex validator;
		std::vector<std::string> _cmdBuffer;
		std::vector<std::string> _fileBuffer;
		Plazza::Task::Criteria _cur;
	};
};
