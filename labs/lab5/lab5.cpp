#include "lab5.h"

std::string lab5::Money::get_info(void) 
{
	std::stringstream ss;
	ss << "Номинал купюр: " << this->first << std::endl
		<< "Количество купюр: " << this->second << std::endl;
	return ss.str();
}

bool lab5::Money::is_enough(int purchase) 
{
	return this->first * this->second >= purchase;
}

int lab5::Money::how_many_allow(int purchase)
{
	for (int amount = 0; true; amount++)
	{
		if (purchase * amount > this->first * this->second)
		{
			return amount - 1;
		}
	}
}

lab5::Money lab5::Money::operator++(int) 
{
	Money buffer = *this;
	++(this->first);
	++(this->second);
	return buffer;
}

lab5::Money& lab5::Money::operator++() 
{
	this->first++;
	this->second++;
	return *this;
}

lab5::Money lab5::Money::operator--(int)
{
	Money buffer = *this;
	--(this->first);
	--(this->second);
	if (this->first < 0 || this->second < 0) 
		throw std::exception("Денежное значение вне доступного диапазона");
	return buffer;
}

lab5::Money& lab5::Money::operator--()
{
	this->first--;
	this->second--;
	if (this->first < 0 || this->second < 0)
		throw std::exception("Денежное значение вне доступного диапазона");
	return *this;
}

bool lab5::Money::operator!() 
{
	return this->second != 0;
}

lab5::Money& lab5::Money::operator+(int value) 
{
	this->second += value;
	return *this;
}

int& lab5::Money::operator[] (int index)
{
	switch (index)
	{
	case 0: return first;
	case 1: return second;
	default: throw std::exception("Значение индекс вне доступного предела");
	}
}

void lab5::lab(void) 
{
	int first, second, select_operation, value_operation;
	string readline;

	cout << "Введите значение номала купюры: ";
	cin >> first;

	cout << "Введите значение количества купюр: ";
	cin >> second;

 	Money money(first, second);
	while (true) 
	{
		system("cls");
		cout << "[ Выберите операцию ] "						<< endl
			<< "$1 - Вывести информацию"						<< endl
			<< "$2 - Определить хватит ли денежных средств"		<< endl
			<< "$3 - Сколько штук товара (n руб.) можно купить" << endl
			<< "$4 - Получить значение поля FIRST"				<< endl
			<< "$5 - Установить значение поля FIRST"			<< endl
			<< "$6 - Получить значение поля SECOND"				<< endl
			<< "$7 - Установить значение поля SECOND"			<< endl
			<< "$8 - Рассчитать сумму денег"					<< endl
			<< "$9 - Произвести индексацию объекта"				<< endl
			<< "$10 - Операция [++]"							<< endl
			<< "$11 - Операция [--]"							<< endl
			<< "$12 - Операция [!]"								<< endl
			<< "$13 - Операция [+]"								<< endl
			<< "$14 - Выход из программы"				<< endl << endl;

		cout << "Введите номер: ";
		getline(cin, readline);
		try
		{
			select_operation = stoi(readline);
		}
		catch (std::exception) 
		{
			cout << endl << "Ошибка при вводе" << endl;
			continue;
		}

		system("cls");
		switch (select_operation)
		{
		case 1:
			cout << money.get_info() << endl;
			break;

		case 2:
			cout << "Введите сумму покупки: ";
			cin >> value_operation;
			cout << (money.is_enough(value_operation) ? "Хватит" : "Не хватит") << endl;
			break;

		case 3:
			cout << "Введите стоимость товара: ";
			cin >> value_operation;
			cout << "Возможно купить: " << money.how_many_allow(value_operation) << " шт." << endl;
			break;

		case 4:
			cout << "Значение поля FIRST: " << money.get_first() << endl;
			break;

		case 5:
			cout << "Введите значение FIRST: ";
			cin >> value_operation;
			money.set_first(value_operation);
			break;

		case 6:
			cout << "Значение поля SECOND: " << money.get_second() << endl;
			break;

		case 7:
			cout << "Введите значение SECOND: ";
			cin >> value_operation;
			money.set_second(value_operation);
			break;

		case 8:
			cout << "Общая сумма денег: " << money.get_sum() << endl;
			break;

		case 9:
			cout << "[0] - FIRST\t[1] - SECOND" << endl << "Введите индекс: ";
			cin >> value_operation;
			try 
			{
				cout << "Значение элемента: " << money[value_operation] << endl;
			}
			catch (std::exception error) 
			{
				cout << error.what() << endl;
			}
			break;

		case 10:
			cout << money.get_info() << endl;
			money++;
			cout << "Совершена операция [++]" << endl
				<< money.get_info() << endl;
			break;

		case 11:
			try 
			{
				cout << money.get_info() << endl;
				money--;
				cout << "Совершена операция [--]" << endl
					<< money.get_info() << endl;
			}
			catch (std::exception error) 
			{
				money++;
				cout << error.what() << endl;
			}
		
			break;

		case 12:
			cout << "Результат операции [!]" << endl
				<< (!money ? "true" : "false") << endl;
			break;

		case 13:
			int value;
			cout << "Введите значение скаляра: ";
			cin >> value;
			money = money + value;
			break;

		case 14: return;
		default:
			cout << "Введен неверный номер" << endl;
		}
		
		cout << endl;
		system("pause");
	}

}