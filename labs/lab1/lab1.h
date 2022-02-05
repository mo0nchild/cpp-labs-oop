#pragma once
#include <iostream>
#include <locale>

#define _USE_MATH_DEFINES
#include <cmath>

using std::cout;
using std::endl;
using std::cin;

namespace lab1 
{
	class task_object 
	{
	public:
		virtual bool run() = 0;
	};


	class task1 : public task_object 
	{
	public:
		task1() 
		{ }

		bool run() override
		{
			cout << "hello" << endl;
			return true;
		}
	};

	class task2 : public task_object
	{
	public:
		task2()
		{ }

		bool run() override
		{
			cout << "hello from 2" << endl;
			return true;
		}
	};


	class task_runner 
	{
	public:
		task_runner operator << (task_runner runner)
		{
			return task_runner(runner.task);
		}

		task_runner(task_object *task)
		{ 
			this->task = task;
		}

		void start(void) 
		{
			task->run();
		}

	private:
		task_object* task;
	};
}
