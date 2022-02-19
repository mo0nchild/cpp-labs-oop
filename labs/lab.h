#pragma once
#include <iostream>
#include <vector>
#include <string>

class Task
{
	std::string name;
public:
	Task(std::string name) : name(name)
	{ }

	std::string get_name(void) { return name; }
	virtual bool run_task(void)
	{
		std::cout << "Based" << std::endl;
		return true;
	}
};

class Lab
{
	std::vector<Task> tasks;
public:

	Lab(std::vector<Task> tasks) : tasks(tasks)
	{ }

	void run_lab()
	{
		for (auto i : tasks)
		{
			std::cout << i.get_name() << std::endl;
			i.run_task();
		}
	}
};

class Task1 : public Task
{
public:
	Task1(std::string name) : Task(name)
	{ }

	bool run_task() override
	{
		std::cout << "Hello from task 1" << std::endl;
		return true;
	}
};

class Task2 : public Task
{
public:
	Task2(std::string name) : Task(name)
	{ }

	bool run_task() override
	{
		std::cout << "Hello from task 2" << std::endl;
		return true;
	}
};

class Task3 : public Task
{
public:
	Task3(std::string name) : Task(name)
	{ }

	bool run_task() override
	{
		std::cout << "Hello from task 3" << std::endl;
		return true;
	}
};