#define _USE_MATH_DEFINES
#include <iostream>
#include <locale>


#include <cmath>

using namespace std;

namespace task1
{
	double function(double a, double b)
	{
		return atan((sin(pow(a, 2.)) + pow(b, 3.)) / sqrt(1. + (b) / (a + cos(M_PI * pow(b, 2.)))));
	}
	bool run(void)
	{
		try 
		{
			double a, b;

			cout << "Введите числа (a b): ";
			cin >> a >> b;

			cout << "Сумма чисел A и B равна " << function(a, b) << endl;
		}
		
		catch (std::exception ex)
		{
			return false;
		}
		return true;
	}
}

namespace task2
{

#define EBSILON 0.001
#define stack_without_fall 100

	double function(double x)
	{
		double current_state = 0, iter, sum = 0;

		auto my_pow = [&](double x, int n)
		{
			double result = 1;
			for (int i = 0; i < n; i++) result *= x;
			
			return result;
		};

		for (int n = 1; true; n++)
		{
			iter = (n % 2 == 0 ? -1 : 1) * (my_pow(x, 2 * n - 1) / (2 * n - 1));
			sum += iter;
			if (current_state != 0)
			{
				if (fabs(current_state - iter) <= EBSILON)
				{
					return sum;
				}
			}
			current_state = iter;

			if (n >= stack_without_fall) return 'a';
		}
	}

	bool run(void)
	{
		try
		{
			double x;

			cout << "Введите X: ";
			cin >> x;

			cout << "F(x): " << function(x) << endl;
		}

		catch (std::exception ex)
		{
			return false;
		}
		return true;
	}
}

namespace task3 
{
	void task1() 
	{
		const int n = 10;
		for(int i = 1; i < n ;i++)
		{
			if (n % i == 0) cout << i << endl;
		}
	}

	void task2()
	{
		int i, fn, n, y;


	}

	bool run(void)
	{
		try
		{
			task1();
		}
		catch (std::exception ex)
		{
			return false;
		}
		return true;
	}
}

namespace task4
{
	bool run(void)
	{
		try
		{
			int n;
			cout << "Введите числа: ";
			cin >> n;

			if (n > 0) cout << "Число положительное" << endl;
			else cout << "Число неположительное" << endl;
		}

		catch (std::exception ex)
		{
			return false;
		}
		return true;
	}
}

void lab(void)
{
	cout << fixed;
	cout.precision(4);


	bool exit_trigger = false, error_handler = true;

	while (1)
	{
		cin.clear();
		int task_number = -1;
		cout << endl
			<< "1 - Проверка Задачи 1\n"
			<< "2 - Проверка Задачи 2\n"
			<< "3 - Проверка Задачи 3\n"
			<< "4 - Проверка Задачи 4\n"
			<< "5 - Выход из программы" << endl << endl;

		cout << "Введите номер задания: " << endl;
		cin >> task_number;

		switch (task_number)
		{
		case 1:
			error_handler = task1::run();

			break;

		case 2:
			error_handler = task2::run();

			break;

		case 3:
			error_handler = task3::run();

			break;

		case 4:
			error_handler = task4::run();

			break;

		case 5: exit_trigger = true; break;

		default:cout << "Неверный ввод" << endl;

		}

		if (!error_handler) cout << "При выполнении задания возникла ошибка\n" << endl;
		if (exit_trigger) break;

	}
}


#include "labs/lab1/lab1.h"
using lab1::task_runner;

int main(void)
{
	setlocale(LC_ALL, "rus");
	
	task_runner *runner = new task_runner(new lab1::task1());
	runner->start();

	*runner = *runner << task_runner(new lab1::task2());
	runner->start();

	delete runner;

	return 0;
}
