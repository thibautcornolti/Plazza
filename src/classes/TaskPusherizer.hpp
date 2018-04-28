/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** TaskPusherizer
*/

#pragma once

#include "Task.hpp"

namespace Plazza {
	class TaskPusherizer {
	public:
		virtual void pushTask(Plazza::Task &task) = 0;

	protected:
	private:
	};
};
