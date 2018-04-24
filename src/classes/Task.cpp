/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include <iostream>
#include <map>

#include "Task.hpp"

Plazza::Task::Task(
	Plazza::Task::Type type, const std::string &file, Criteria criteria)
	: _type(type), _criteria(criteria), _file(file)
{
}

Plazza::Task::Task()
	: Plazza::Task::Task(Plazza::Task::Type::EXIT, "",
		  Plazza::Task::Criteria::EMAIL_ADDRESS)
{
}

Plazza::Task::Task(const Task &task)
{
	_type = task._type;
	_file = task._file;
	_criteria = task._criteria;
}

Plazza::Task::~Task()
{
}

Plazza::Task::Type Plazza::Task::getType() const
{
	return _type;
}

const std::string &Plazza::Task::getFile() const
{
	return _file;
}

Plazza::Task::Criteria Plazza::Task::getCriteria() const
{
	return _criteria;
}

std::ostream &operator<<(std::ostream &s, const Plazza::Task &task)
{
	std::map<Plazza::Task::Type, std::string> type{
		{Plazza::Task::Type::SCRAP, "Scrap"},
		{Plazza::Task::Type::EXIT, "Exit"},
		{Plazza::Task::Type::NOOP, "No-op"}};
	std::map<Plazza::Task::Criteria, std::string> crit{
		{Plazza::Task::Criteria::IP_ADDRESS, "IP_ADDRESS"},
		{Plazza::Task::Criteria::PHONE_NUMBER, "PHONE_NUMBER"},
		{Plazza::Task::Criteria::EMAIL_ADDRESS, "EMAIL_ADDRESS"}};

	s << "<Task " << type.at(task.getType());
	if (task.getType() == Plazza::Task::Type::SCRAP) {
		s << " " << task.getFile() << " ";
		s << crit.at(task.getCriteria());
	}
	s << ">";
	return s;
}
