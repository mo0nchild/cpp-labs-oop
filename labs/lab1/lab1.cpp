#include "lab1.h"

using namespace lab1;


void task_runner::start(void) 
{
	task->run();
}


bool task1::run()
{
	cout << "hello from first task" << endl;
	return true;
}

bool task2::run() 
{
	cout << "hello from seconde task" << endl;
	return true;
}