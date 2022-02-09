#include "lab1.h"
using namespace lab1;


double task1::function(double a, double b)
{
	return atan((sin(pow(a, 2.)) + pow(b, 3.)) / sqrt(1. + (b) / (a + cos(M_PI * pow(b, 2.)))));
}

bool task1::run(void)
{
	cout << fixed;
	cout.precision(4);
	try
	{
		double a, b;

		cout << "������� ����� (a b): ";
		cin >> a >> b;

		cout << "����� ����� A � B ����� " << function(a, b) << endl;
	}

	catch (...)
	{
		return false;
	}
	return true;
}

double task2::function(double x)
{
	double current_state = 0, iter, sum = 0;

	for (int n = 1; true; n++)
	{

		iter = pow(-1., n - 1) * (pow(x, 2. * n - 1) / (2. * n - 1));
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

bool task2::run(void)
{
	try
	{
		double x;

		cout << "������� X: ";
		cin >> x;

		cout << "F(x): " << function(x) << endl;
	}

	catch (...)
	{
		return false;
	}

	return true;
}

void task3::subtask1(void)
{
	cout << "������� n: ";
	int n;
	cin >> n;

	cout << "�����: ";
	for (int i = 1; i <= n; i++)
	{
		if (n % i == 0) cout << i << " ,\t";
	}
	cout << endl;
}

void task3::subtask2(void)
{
	int i, fn = 1, n, y = 1;
	cout << "������� n: ";
	cin >> n;

	int delta = (n % 2 != 0) ? 1 : 2;

	for (int i = delta; i <= n; i += delta) fn *= i;

	cout << "�����: " << fn << endl;

}

void task3::subtask3(void)
{
	double fn = 1;
	int n;

	cout << "������� n: ";
	cin >> n;

	double up = 2, down = 1;
	for (int i = 1; i <= n; i++)
	{
		fn *= (up / down);

		if (i % 2 == 0) up += 2;
		else down += 2;
	}

	cout << "�����: " << fn << endl;
}

void task3::subtask4(void)
{
	int n, j;
	double s = 0, x;

	cout << "������� n: ";
	cin >> n;
	cout << "������� x: ";
	cin >> x;

	for (double k = 1; k < n; k++)
	{
		for (double m = k; m < n; m++)
		{
			s += (x + k) / m;
		}
	}

	cout << "�����: " << s << endl;
}

void task3::subtask5(void)
{
	int n, j;
	double s = 0, x;

	cout << "������� n: ";
	cin >> n;
	cout << "������� x: ";
	cin >> x;

	for (double i = 1; i < n; i++)
	{
		for (double j = 1; j < i; j++)
		{
			s += (1.) / (i + 2 * j);
		}
	}

	cout << "�����: " << s << endl;
}

void task3::subtask6(void)
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

	cout << "�����: " << counter << endl;
}

void task3::subtask7(void)
{
	double P = 1;
	for (double i = 1, j = 1; i < 20 && j < 20; i++, j++)
	{
		P *= 1. / (i + j * j);
		cout << P << " ";
	}
	cout << endl;
	cout << "�����: " << P << endl;
}

bool task3::run(void)
{
	try
	{
		void (*tasks[7])(void) = { subtask1, subtask2, subtask3, subtask4, subtask5, subtask6, subtask7 };

		cout << "������� ����� ������� � ������� (1-7): ";
		int n;
		cin >> n;
		n--;

		if (n < 0 || n > 6)
		{
			cout << "������� �� �������" << endl;
			throw std::exception("not found");
		}

		tasks[n]();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool task4::run(void)
{
	try
	{
		int n;
		cout << "������� �����: ";
		cin >> n;

		if (n > 0) cout << "����� �������������" << endl;
		else cout << "����� ���������������" << endl;
	}

	catch (...)
	{
		return false;
	}
	return true;
}
	
void lab1::lab(void)
{

	bool exit_trigger = false, error_handler = true;

	while (1)
	{
		system("cls");
		int task_number = -1;
		cout << endl
			<< "1 - �������� ������ 1\n"
			<< "2 - �������� ������ 2\n"
			<< "3 - �������� ������ 3\n"
			<< "4 - �������� ������ 4\n"
			<< "5 - ����� �� ���������" << endl << endl;

		cout << "������� ����� �������: " << endl;
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
			error_handler = task4::run();
			break;

		case 5:
			exit_trigger = true;
			break;

		default:cout << "�������� ����" << endl;

		}

		if (exit_trigger) break;
		else
		{
			if (!error_handler) cout << "��� ���������� ������� �������� ������\n" << endl;
		}

		system("pause");

	}
}
