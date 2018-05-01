/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** CLICore
*/

#include "CLICore.hpp"

Plazza::CLICore::CLICore(int workerCount) : _pool(workerCount)
{
}

Plazza::CLICore::~CLICore()
{
}

void Plazza::CLICore::start()
{
	_parser.getNextTask();
}
