#pragma once
#include <iostream>
#include <locale>
#include <cmath>
#include <vector>

// для случайной генерации чисел в массив.
#define MAX_ARR_VALUE 10
#define MIN_ARR_VALUE -5

#define CONSOLE_GREEN_COLOR "\033[32m"
#define CONSOLE_RED_COLOR "\033[31m"
#define CONSOLE_BLUE_COLOR "\033[36m"
#define CONSOLE_RESET_COLOR "\033[0m"

namespace lab2
{
	using namespace std;

	double random();

	namespace task1
	{
		double* generate_arr(double* arr, int n);

		double& find_min_positive(double* arr, int n);

		double calculate(double* arr, int n);

		void print_arr(double* arr, int n);

		bool run(void);
	}

	namespace task2
	{
		using matrix_t = vector<vector<int>>;

		matrix_t generate_matrix(int n, int m);

		bool run(void);
	}

	namespace task3
	{
		int* sort_merge(int* arr, int n);

		bool run(void);
	}

	void lab(void);

}