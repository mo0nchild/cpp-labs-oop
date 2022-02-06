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

		for (int n = 1; true; n++)
		{

			iter = pow(-1., n-1) * (pow(x, 2. * n - 1) / (2. * n - 1));
			sum += iter;

			if (current_state != 0)
			{
				if (fabs(current_state - iter) <= EBSILON) break;
			}
			current_state = iter;
			//if (n >= stack_without_fall) return 0;
		}
		return sum;
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
	void task1(void) 
	{
		cout << "Введите n: ";
		int n;
		cin >> n;

		cout << "Вывод: ";
		for(int i = 1; i < n ;i++)
		{
			if (n % i == 0) cout << i << " ,\t";
		}
		cout << endl;
	}

	void task2(void)
	{
		int i, fn = 1, n, y = 1;
		cout << "Введите n: ";
		cin >> n;


		int delta = (n % 2 != 0) ? 1 : 2;

		for (int i = delta; i <= n; i += delta)
		{
			fn *= i;
		}
		
		cout << "Вывод: " << fn << endl;

	}

	void task3(void) 
	{
		double fn = 1;
		int n;

		cout << "Введите n: ";
		cin >> n;

		double up = 2, down = 1;
		for (int i = 1; i <= n; i++) 
		{
			fn *= (up / down);

			if (i % 2 == 0) up += 2;
			else down += 2;
		}

		cout << "Вывод: " << fn << endl;
	}

	void task4(void) 
	{
		int n, j;
		double s = 0, x;

		cout << "Введите n: ";
		cin >> n;
		cout << "Введите x: ";
		cin >> x;

		for (double k = 1; k < n; k++) 
		{
			for (double m = k; m < n; m++) 
			{
				s += (x + k) / m;
			}
		}

		cout << "Вывод: " << s << endl;
	}

	void task5(void)
	{
		int n, j;
		double s = 0, x;

		cout << "Введите n: ";
		cin >> n;
		cout << "Введите x: ";
		cin >> x;

		for (double i = 1; i < n; i++)
		{
			for (double j = 1; j < i; j++)
			{
				s += (1.) / (i + 2 * j);
			}
		}

		cout << "Вывод: " << s << endl;
	}

#define MAX_GENERATE 1000
#define MIN_GENERATE 100

	void task6(void)
	{
		srand(time(0));
		double arr[200];

		for (int i = 0; i < 200; i++) 
		{
			arr[i] = (double)(MIN_GENERATE + rand() % (MAX_GENERATE + 1))
				/ (double)(MIN_GENERATE + rand() % (MAX_GENERATE + 1));
			cout << arr[i] << "\t";
		}
		cout << endl;

		int counter = 0;
		for (int i = 1; i < 199; i++) 
		{
			if (arr[i - 1] < arr[i] && arr[i] > arr[i + 1]) counter++;
		}

		cout << "Вывод: " << counter << endl;
	}

	void task7(void)
	{
		double P = 1;
		for (double i = 1; i < 20; i++) 
		{
			for (double j = 1; j < 20; j++)
			{
				P *= 1. / (i + j * j);
				cout << P << " ";
			}
		}
		cout << endl;
		cout << "Вывод: " << P << endl;
	}

	bool run(void)
	{
		try
		{
			void (*tasks[7])(void) = { task1, task2, task3, task4, task5, task6, task7 };

			cout << "Введите номер задания с ошибкой (1-7): ";
			int n;
			cin >> n;
			if (--n < 0 || n > 6) 
			{
				cout << "Задание не найдено" << endl;
				throw std::exception("not found");
			}

			tasks[n]();
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
			cout << "Введите число: ";
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

		case 5: 
			exit_trigger = true; 
			break;

		default:cout << "Неверный ввод" << endl;

		}

		if (!error_handler) cout << "При выполнении задания возникла ошибка\n" << endl;
		if (exit_trigger) break;

	}
}

int main(void)
{
	setlocale(LC_ALL, "rus");
	lab();

	return 0;
}
