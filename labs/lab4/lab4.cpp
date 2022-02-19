#include "lab4.h"
using namespace lab4;

bool task1::run(void) 
{
	string str;
	int counter = 0;

	try 
	{
		while (true)
		{	
			system("cls");
			cout << "Введите строку для обработки: " << endl;

			getline(cin, str);
			if (str.find("exit") != string::npos) break;

			counter = 0;
			for (int i = 0; i < str.size(); i++)
			{
				if(str[i] == ' ')counter++;
			}

			cout << "Количество пробелов: " << counter << endl;
			system("pause");
		}
	}
	catch (std::exception) { return false; }
	
	return true;
}

vector<string> task2::read_file(const char* path) 
{
	vector<string> result;
	ifstream file(path, ios::in);
	string line;

	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			result.push_back(line);
		}
		file.close();
	}
	return result;
}

bool task2::write_file(const char* path, const vector<string>& data) 
{
	ofstream file(path, ios::out);

	if (file.is_open())
	{
		for (string i : data) file << i << endl;
		file.close();
	}
	else return false;

	return true;
}

bool task2::run(void)
{
	vector<string> buffer;
	try
	{
		if ((buffer = read_file(FILE_PATH_INPUT)).size() == 0) 
		{
			throw std::exception("Не удалось прочитать файл");
		}

		int current_length = 0;
		int min = -1, min_line = 0, min_pos = 0;

		for (int line_index = 0; line_index < buffer.size(); line_index++)
		{
			int marker = 0;
			string& line = buffer[line_index];

			if (current_length != 0) 
			{
				marker = -current_length;
			}

			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == '.') 
				{
					current_length = fabs(i - marker);
					if (current_length < min || min == -1)
					{
						min = current_length, min_pos = marker, min_line = line_index;
					}
					marker = i + 1;
				}
			}
			current_length = fabs(line.size() - marker);
		}
		
		if (min_pos < 0) 
		{
			buffer[min_line - 1] = buffer[min_line - 1].substr(0, buffer[min_line - 1].size() + min_pos);
			min_pos = 0;
		}

		string& select_line = buffer[min_line];
		for (int i = min_pos; i < select_line.size(); i++)
		{
			if (select_line[i] == '.')
			{
				select_line = select_line.substr(0, min_pos) + "С новым годом!"
					+ select_line.substr(i + 1, fabs(select_line.size() - i));
				break;
			}
		}
		
		if(!write_file(FILE_PATH_OUTPUT, buffer)) throw std::exception("Не удалось записать в файл");
		cout << "Файл сохранен. Выполнение задания завершилось." << endl;
	}
	catch (std::exception error) 
	{
		cout << error.what() << endl;
		return false;
	}

	return true;
}

string task3::get_info(const MARSH& marsh) 
{
	return ("\tНомер маршрута: " + to_string(marsh.NUMER)) 
		+ ("\tВремя в пути: " + to_string(marsh.TIME)) 
		+ ("\n\tНачальный пункт: " + marsh.BEGST) 
		+ ("\n\tКонечный пункт: " + marsh.TERM);
}

vector<task3::MARSH> task3::contained_point(MARSH* arr, uint16_t size, 
	function<bool(MARSH&)> checker)
{
	vector<task3::MARSH> result;
	for(uint16_t i = 0; i < size; i++)
	{
		if (checker(arr[i])) result.push_back(arr[i]);
	}
	return result;
}

template<typename T> 
void task3::input_variable(const char* message, T& out_variable) 
{
	string read_line;
	stringstream str_stream;

	cin.clear();
	fflush(stdin);

	cout << message << endl;
	std::getline(std::cin, read_line);
	
	str_stream << read_line;
	str_stream >> out_variable;

	if (str_stream.fail()) 
	{
		str_stream.clear();
		throw std::exception("Несоответсвие типа");
	}
}

bool task3::run(void)
{
	MARSH TRAFIC[MARSH_LIST_SIZE];

	cout << fixed;
	cout.precision(MY_PRECISION);

	for (int i = 0; i < MARSH_LIST_SIZE; i++)
	{
		system("cls");
		try 
		{
			cout << "Номер элемента: " << (i + 1) << endl << endl;
			input_variable<int>("Введите номер маршрута: ", TRAFIC[i].NUMER);
			input_variable<double>("Введите время в пути: ", TRAFIC[i].TIME);

			input_variable<string>("Введите название начального пункта: ", TRAFIC[i].BEGST);
			input_variable<string>("Введите название конечного пункта: ", TRAFIC[i].TERM);
		}
		catch (std::exception error) 
		{
			cout << error.what() << endl << endl;
			system("pause");

			i--;
			continue;
		}
	}

	string point_find;
	while (1)
	{
		fflush(stdin);
		system("cls");
		cout << "Введите название пункта для поиска (exit чтобы выйти): ";

		getline(cin, point_find);
		if (point_find.find("exit") != string::npos) break;

		vector<MARSH> found = contained_point(TRAFIC, MARSH_LIST_SIZE,
			[&point_find](const MARSH& marsh) -> bool {
				return marsh.BEGST == point_find || marsh.TERM == point_find;
			});

		for (auto i : found) cout << get_info(i) << endl;

		if (found.size() == 0) cout << "Такой пункт не найден" << endl;
		system("pause");
	}

	return true;
}


void lab4::lab(void) 
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