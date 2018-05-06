//
// EPITECH PROJECT, 2018
// scrapper.cpp
// File description:
// scrapper.cpp
//

#include "Scrapper.hpp"

Plazza::Scrapper::Scrapper(Task &task, ClientUnixSocket &logger)
{
	this->_task = task;
	this->_logger = logger;
	this->_type = this->_task.getType();
	this->_criteria = this->_task.getCriteria();
	this->_file = this->_task.getFile();
}

Plazza::Scrapper::~Scrapper()
{
}

void Plazza::Scrapper::startScrapper()
{
	std::ifstream ifs(this->_file);
	std::smatch m;
	std::string buf;

	if (ifs)
		std::getline(ifs, buf, '\0');
	else
		_logger.send(
			"Error: Couldn't open file '" + this->_file + "'\n");
	ifs.close();
	std::string::const_iterator i(buf.cbegin());
	while (std::regex_search(i, buf.cend(), m, _criteriaRegs[_criteria])) {
		_logger.send(m[(this->_criteria ==
				       Plazza::Task::Criteria::IP_ADDRESS)]
				     .str() +
			"\n");
		i += m.position() + m.length();
	}
}
