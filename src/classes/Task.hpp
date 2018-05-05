/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

#include <string>

namespace Plazza {
	class Task {
	public:
		enum Type {
			SCRAP,
			EXIT,
			NOOP,
		};
		enum Criteria {
			PHONE_NUMBER,
			EMAIL_ADDRESS,
			IP_ADDRESS,
			CUSTOM
		};

		Task(Type, const std::string &, Criteria);
		Task();
		Task(const Task &);
		~Task();
		Task &operator=(const Task &) = default;

		Type getType() const;
		const std::string &getFile() const;
		Criteria getCriteria() const;
		std::string getStringifiedCriteria() const;

		void setType(Type type);
		void setFile(const std::string &file);
		void setCriteria(Criteria criteria);

	protected:
	private:
		Type _type;
		Criteria _criteria;
		std::string _file;
	};
};

std::ostream &operator<<(std::ostream &s, const Plazza::Task &);
Plazza::Task &operator>>(std::istream &s, Plazza::Task &);
