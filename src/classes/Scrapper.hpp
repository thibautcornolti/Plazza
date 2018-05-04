//
// EPITECH PROJECT, 2018
// Scrapper.hpp
// File description:
// Scrapper.hpp
//

#pragma once

#include <iostream>
#include <regex>
#include <fstream>
#include <cstring>
#include "socket/ClientUnixSocket.hpp"
#include "Task.hpp"

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
	  };
}
