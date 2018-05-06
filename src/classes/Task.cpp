/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

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

std::string Plazza::Task::getStringifiedCriteria() const
{
	std::map<Plazza::Task::Criteria, std::string> crit{
		{Plazza::Task::Criteria::IP_ADDRESS, "IP_ADDRESS"},
		{Plazza::Task::Criteria::PHONE_NUMBER, "PHONE_NUMBER"},
		{Plazza::Task::Criteria::EMAIL_ADDRESS, "EMAIL_ADDRESS"}};
	return (getType() == Plazza::Task::EXIT ? "" : crit.at(getCriteria()));
}

void Plazza::Task::setType(Plazza::Task::Type type)
{
	_type = type;
}

void Plazza::Task::setFile(const std::string &file)
{
	_file = file;
}

void Plazza::Task::setCriteria(Plazza::Task::Criteria criteria)
{
	_criteria = criteria;
}

std::ostream &operator<<(std::ostream &s, const Plazza::Task &task)
{
	std::map<Plazza::Task::Type, std::string> type{
		{Plazza::Task::Type::SCRAP, "Scrap"},
		{Plazza::Task::Type::EXIT, "Exit"},
		{Plazza::Task::Type::NOOP, "No-op"}};

	s << "<Task " << type.at(task.getType());
	if (task.getType() == Plazza::Task::Type::SCRAP) {
		s << " " << task.getFile() << " ";
		s << task.getStringifiedCriteria();
	}
	s << ">";
	return s;
}

Plazza::Task &operator>>(std::istream &s, Plazza::Task &task)
{
	std::map<std::string, Plazza::Task::Type> type{
		{"Scrap", Plazza::Task::Type::SCRAP},
		{"Exit>", Plazza::Task::Type::EXIT},
		{"No-op>", Plazza::Task::Type::NOOP}};
	std::map<std::string, Plazza::Task::Criteria> crit{
		{"IP_ADDRESS>", Plazza::Task::Criteria::IP_ADDRESS},
		{"PHONE_NUMBER>", Plazza::Task::Criteria::PHONE_NUMBER},
		{"EMAIL_ADDRESS>", Plazza::Task::Criteria::EMAIL_ADDRESS}};
	std::string out;
	s >> out;
	if (out == "<Task") {
		s >> out;
		task.setType(type.at(out));
		if (task.getType() == Plazza::Task::Type::SCRAP) {
			s >> out;
			task.setFile(out);
			s >> out;
			task.setCriteria(crit.at(out));
		}
	}
	return task;
}
