#include "lab2.h"
using namespace lab2;


double* task1::generate_arr(double* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = random();
	}
	return arr;
}

double task1::find_min_positive(double* arr, int n)
{
	double min = INFINITY;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < min && arr[i] > 0) min = arr[i];

	}
	return (min == INFINITY) ? 0 : min;
}

double task1::calculate(double* arr, int n)
{
	double result = 1;
	for (int i = 0; i < n; i++)
	{
		result *= (arr[i] != 0) ? arr[i] : 1;
	}
	return result;
}

bool task1::run(void)
{
	bool error_state = true;
	int N;

	cout << "Кол-во элементов массива: ";
	cin >> N;
	cout << endl;

	double* arr = new double[N]();

	try
	{
		// 1 подзадание
		arr = generate_arr(arr, N);
		cout << "Элементы: " << endl;
		for (int i = 0; i < N; i++)
		{
			cout << arr[i] << endl;
		}
		cout << endl;

		// 2 подзадание
		double min = find_min_positive(arr, N);
		cout << "Минимальное положительное: ";
		if (min) cout << min;
		else cout << "Не найдено";
		cout << endl;

		// 3 подзадание
		cout << "Произведение не нулевых элементов: " << calculate(arr, N) << endl;

		// 4 подзадание
		cout << "Ненулевые элементы в обратном порядке: " << endl;
		for (int i = N - 1; i >= 0; i--)
		{
			if (arr[i] != 0) cout << arr[i] << "\t";
		}
		cout << endl;
	}
	catch (...)
	{
		error_state = false;
	}

	delete[] arr;
	return error_state;
}

task2::matrix_t task2::generate_matrix(int n, int m)
{
	task2::matrix_t arr;

	for (int i = 0; i < n; i++)
	{
		arr.push_back(vector<int>());
		for (int k = 0; k < m; k++)
		{
			arr[i].push_back((double)(MIN_ARR_VALUE + rand() % (MAX_ARR_VALUE + 1)));
		}
	}
	return arr;
}

bool task2::run(void)
{
	int n, m;
	bool error_state = true;

	cout << "Введите число n и m: ";
	cin >> n >> m;
	cout << endl;

	int* counter = new int[m]();
	try
	{
		//m - column / n - row
		task2::matrix_t matrix = generate_matrix(n, m);

		for (vector<int> arr : matrix)
		{
			for (int k = 0; k < arr.size(); k++)
			{

				if (arr[k] > 0)
				{
					cout << "\033[32m"; // green color
					(*(counter + k))++;
				}
				else if (arr[k] < 0)
				{
					cout << "\033[31m"; // red color
					(*(counter + k))--;
				}
				else cout << "\033[36m"; // blue color

				cout << arr[k] << "\033[0m" << "\t";

			}
			cout << endl << endl;
		}

		bool trigger = false;
		cout << "Смещение равновесия: " << endl;
		for (int i = 0; i < m; i++)
		{
			if (counter[i] == 0 && !trigger) trigger = true;
			cout << counter[i] << "\t";
		}
		cout << endl << "В матрице " << ((trigger) ? "есть столбец" : "нету столбца")
			<< " с равным количеством положительных и отрицательных" << endl;


	}
	catch (...)
	{
		error_state = false;
	}

	delete[] counter;
	return error_state;
}

int* task3::sort_merge(int* arr, int n)
{
	if (n > 1)
	{
		int* arr_left = sort_merge(arr, n / 2);
		int* arr_right = sort_merge(arr + (n / 2), n - (n / 2));

		int* new_arr = new int[n]();
		int left_cursor = 0, right_cursor = 0;

		for (int i = 0; i < n; i++)
		{
			if (left_cursor < (n / 2) && right_cursor < n - (n / 2))
			{
				if (arr_left[left_cursor] < arr_right[right_cursor])
				{
					new_arr[i] = arr_left[left_cursor++];
				}
				else new_arr[i] = arr_right[right_cursor++];
			}
			else
			{
				if (left_cursor == n / 2)
				{
					new_arr[i] = arr_right[right_cursor++];
				}
				else if (right_cursor == n - (n / 2))
				{
					new_arr[i] = arr_left[left_cursor++];
				}
			}
		}
		for (int i = 0; i < n; i++) arr[i] = new_arr[i];

		delete[] new_arr;
	}
	for (int i = 0; i < n; i++) cout << arr[i] << " ";
	cout << endl;

	return arr;
}

bool task3::run(void)
{
	int n;
	bool error_state = true;

	cout << "Введите значение размера массива: ";
	cin >> n;

	int* arr = new int[n];
	try
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = random();
			cout << arr[i] << " ";
		}
		cout << endl;
		sort_merge(arr, n);
	}
	catch (...)
	{
		error_state = false;
	}

	delete[] arr;
	return error_state;
}

double lab2::random()
{
	return (double)(MIN_ARR_VALUE + rand() % (MAX_ARR_VALUE + 1));
}

void lab2::lab(void)
{
	cout << fixed;
	cout.precision(4);

	bool exit_trigger = false, error_handler = true;
	srand(time(0));

	while (1)
	{
		system("cls");
		int task_number = -1;
		cout << endl
			<< "1 - Проверка Задачи 1\n"
			<< "2 - Проверка Задачи 2\n"
			<< "3 - Проверка Задачи 3\n"
			<< "4 - Выход из программы" << endl << endl;

		cout << "Введите номер задания: " << endl;
		cin >> task_number;
		system("cls");

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
			exit_trigger = true;
			break;

		default:cout << "Неверный ввод" << endl;
		}

		if (exit_trigger) break;
		else
		{
			if (!error_handler) cout << "При выполнении задания возникла ошибка\n" << endl;
		}

		system("pause");
	}
}

