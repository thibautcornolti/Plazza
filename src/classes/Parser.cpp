/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Parser
*/

#include "Parser.hpp"

const std::regex Plazza::Parser::validator("^[^\\s]+(?:\\s+[^\\s]+?)*\\s+(?:"
					   "IP_ADDRESS|PHONE_NUMBER|EMAIL_"
					   "ADDRESS)$");

Plazza::Parser::Parser()
{
}

Plazza::Parser::~Parser()
{
}

std::vector<std::string> Plazza::Parser::split(
	const std::string &in, const std::string &pattern)
{
	auto reg = std::regex(pattern);
	std::string ref = in;
	std::string ret = "";
	std::smatch s;
	std::vector<std::string> v;

	while (std::regex_search(ref, s, reg)) {
		v.push_back(ref.substr(0, s.position(0)));
		ref = ref.substr(s.position(0) + s.length(0));
	}
	if (ref.empty() == false)
		v.push_back(ref);
	return v;
}

std::string Plazza::Parser::replace(const std::string &in,
	const std::string &pattern, const std::string &pholder)
{
	auto ret = in;
	auto reg = std::regex(pattern);
	std::smatch s;

	while (std::regex_search(ret, s, reg)) {
		ret = ret.replace(s.position(0), s.length(0), pholder);
	}
	return ret;
}

Plazza::Task Plazza::Parser::parseNextCommand(
	Plazza::Task task, std::string line)
{
	line = Plazza::Parser::replace(line, "(?:^\\s+)|(?:\\s+$)", "");
	if (std::regex_match(line, std::regex(Plazza::Parser::validator))) {
		auto v = Plazza::Parser::split(line, "\\s+");
		_cur = tab.at(v.back());
		v.pop_back();
		for (auto &elem : v)
			_fileBuffer.push_back(elem);
		task = Plazza::Parser::getNextTask();
	} else
		task.setType(Plazza::Task::NOOP);
	return task;
}

Plazza::Task Plazza::Parser::getNextTask()
{
	Plazza::Task task;

	if (_fileBuffer.size()) {
		std::string file = _fileBuffer.front();
		_fileBuffer.erase(_fileBuffer.begin());
		task = Plazza::Task(Plazza::Task::Type::SCRAP, file, _cur);
	}
	else {
		std::string line;
		if (_cmdBuffer.size() == 0 && std::cin.eof() == false) {
			std::getline(std::cin, line, '\n');
			_cmdBuffer = Plazza::Parser::split(line, ";");
		}
		if (_cmdBuffer.size()) {
			line = _cmdBuffer.front();
			_cmdBuffer.erase(_cmdBuffer.begin());
			task = Plazza::Parser::parseNextCommand(task, line);
		}
	}
	return task;
}
