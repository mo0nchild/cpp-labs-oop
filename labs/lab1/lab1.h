#define _USE_MATH_DEFINES

#include <iostream>
#include <locale>
#include <cmath>

// для задания 2
#define EBSILON 0.001
#define stack_without_fall 100

// для генерации чисел
#define MAX_GENERATE 1000
#define MIN_GENERATE 100


namespace lab1 
{
	using namespace std;

	namespace task1
	{
		double function(double a, double b);
		bool run(void);
	}

	namespace task2
	{
		double function(double x);
		bool run(void);
	}

	namespace task3
	{
		void subtask1(void);
		void subtask2(void);
		void subtask3(void);
		void subtask4(void);
		void subtask5(void);
		void subtask6(void);
		void subtask7(void);

		bool run(void);
	}

	namespace task4
	{
		bool run(void);
	}

	void lab(void);
}