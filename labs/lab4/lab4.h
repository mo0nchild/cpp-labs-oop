#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include <cmath>

namespace lab4 
{
	using namespace std;

	// Получить от пользователя строку текста и Подсчитать количество пробелов в строке.
	// Вывести полученное значение на экран.Повторять до тех пор, пока не встретится
	// строка завершающаяся словом quit
	namespace task1 { bool run(void); }

	// Открыть текстовый файл в необходимом режиме(на чтение, на чтение и запись, надобавление). 
	// (В файле должно быть не менее 30 строк). Найти самую короткое предложение текста и 
	// заменить её фразой "С новым годом!".Записать измененный текст в новый файл.

	namespace task2 
	{
#define FILE_PATH_INPUT ".\\labs\\lab4\\files\\input.txt"
#define FILE_PATH_OUTPUT ".\\labs\\lab4\\files\\output.txt"

		vector<string> read_file (const char* path);
		bool write_file(const char* path, const vector<string>& data);

		bool run(void);
	}

	namespace task3 
	{
#define MY_PRECISION 2
#define MARSH_LIST_SIZE 8

		struct MARSH 
		{
			int NUMER;
			double TIME;
			string BEGST, TERM;
		};
	
		template<typename T = string>
		void input_variable(const char* message, T& out_variable);

		string get_info(const MARSH& marsh);
		vector<MARSH> contained_point(MARSH* arr, uint16_t size, function<bool(MARSH&)> checker);

		bool run(void);
	}

	void lab(void);
}