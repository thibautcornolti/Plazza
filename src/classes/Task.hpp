/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#pragma once

namespace Plazza {
	class Task {
		public:
			enum Type {
				SCRAP,
				EXIT,
				NOOP,
			};

			Task(Type);
			~Task();

			Type getType();
		protected:
		private:
			Type _type;
	};
};