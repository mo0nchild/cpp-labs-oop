#pragma once
#include <iostream>
#include <locale>
#include <cmath>
#include <vector>

#define MAX_ARR_VALUE 10
#define MIN_ARR_VALUE -5


namespace lab2
{
	using namespace std;

	double random();

	namespace task1
	{
		double* generate_arr(double* arr, int n);

		double find_min_positive(double* arr, int n);

		double calculate(double* arr, int n);

		bool run(void);
	}

	// ƒан двумерный массив размером n m, заполненный случайными числами.ќпределить,
	// есть ли в данном массиве столбец, в котором равное количество положительных и
	// отрицательных элементов.
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