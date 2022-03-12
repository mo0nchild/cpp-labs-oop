#include "lab8.h"

using namespace lab8;

int IntegerStreamRead::get_value(string message) const
{
	cout << message << endl;

	string buffer;
	getline(*_stream, buffer);

	stringstream ss(buffer);
	double result = 0;

	ss >> result;
	if (ss.fail())
	{
		ss.clear();
		throw exception("Нельзя конвертировать в целочисленный тип");
	}

	if (result - int(result) != 0)
	{
		throw IntegerException(
			"Передано вещественное число вместо целого",
			ss.str(), IntegerException::CANNOT_CONVERTED
		);
	}

	return int(result);
}

void lab8::lab(void) 
{
	try 
	{
		auto result = lab8::IntegerStreamRead(cin).get_value("Введите число: ");;
		cout << "Результат: " << result << endl;
	}
	catch (const lab8::IntegerException& int_error)
	{
		cout << "Ошибка: " << int_error.what() << endl;
		cout << "Состояние: " << int_error.get_error_state() << endl;
		cout << "Статус: " << int_error.get_status() << endl;
	}
	catch (const std::exception& basic_error)
	{
		cout << "Ошибка: " << basic_error.what() << endl;
	}
	
}