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
#include "Task.hpp"

namespace Plazza {
	  class Scrapper {
	  public:
		  Scrapper(Task &task);
		  ~Scrapper();

		  void startScrapper();

	  protected:
	  private:
		  Task _task;
		  Plazza::Task::Type _type;
		  Plazza::Task::Criteria _criteria;
		  std::string _file;
	  };
}
