/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "Task.hpp"

Plazza::Task::Task(Plazza::Task::Type type)
	: _type(type)
{}

Plazza::Task::~Task()
{}

Plazza::Task::Type Plazza::Task::getType()
{
	return _type;
}
