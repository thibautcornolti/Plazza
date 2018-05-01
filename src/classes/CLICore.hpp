/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** CLICore
*/

#pragma once

#include "Parser.hpp"
#include "SlavePool.hpp"

namespace Plazza {
	class CLICore {
	public:
		CLICore(int workerCount);
		~CLICore();
		void start();

	protected:
	private:
		Plazza::Parser _parser;
		Plazza::SlavePool _pool;
	};
};
