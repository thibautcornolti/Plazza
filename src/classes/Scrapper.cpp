//
// EPITECH PROJECT, 2018
// scrapper.cpp
// File description:
// scrapper.cpp
//

#include "Scrapper.hpp"

Plazza::Scrapper::Scrapper(Task &task)
{
	this->_task = task;
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
	std::regex r;
	std::smatch m;
	std::string buf;

	if (ifs)
		std::getline(ifs, buf, '\0');
	else
		std::cerr << "Error: Couldn't open file '" << this->_file << "'" << std::endl;
	ifs.close();
	if (this->_criteria == Plazza::Task::Criteria::EMAIL_ADDRESS)
		r = "[a-zA-Z0-9_\\.-]+@[a-zA-Z0-9_\\.-]+\\.[a-zA-Z0-9_\\.-]+";
	else if (this->_criteria == Plazza::Task::Criteria::PHONE_NUMBER)
		r = "([0-9]{2}(\\.| )?){4}[0-9]{1,2}";
	else if (this->_criteria == Plazza::Task::Criteria::IP_ADDRESS) {
		r = "(?:\\s|^)((?:[0-9]{1,3}\\.){3}[0-9]{1,3})(?:\\s|$)";
	}
	std::string::const_iterator i(buf.cbegin());
	while (std::regex_search(i, buf.cend(), m, r)) {
		std::cout << m[(this->_criteria == Plazza::Task::Criteria::IP_ADDRESS)] << std::endl;
		i += m.position() + m.length();
	}
}
