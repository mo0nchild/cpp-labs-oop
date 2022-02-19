#include "lab5.h"

std::string lab5::Money::get_info(void) 
{
	std::stringstream ss;
	ss << "������� �����: " << this->first << std::endl
		<< "���������� �����: " << this->second << std::endl;
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
		throw std::exception("�������� �������� ��� ���������� ���������");
	return buffer;
}

lab5::Money& lab5::Money::operator--()
{
	this->first--;
	this->second--;
	if (this->first < 0 || this->second < 0)
		throw std::exception("�������� �������� ��� ���������� ���������");
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
	default: throw std::exception("�������� ������ ��� ���������� �������");
	}
}

void lab5::lab(void) 
{
	int first, second, select_operation, value_operation;
	string readline;

	cout << "������� �������� ������ ������: ";
	cin >> first;

	cout << "������� �������� ���������� �����: ";
	cin >> second;

 	Money money(first, second);
	while (true) 
	{
		system("cls");
		cout << "[ �������� �������� ] "						<< endl
			<< "$1 - ������� ����������"						<< endl
			<< "$2 - ���������� ������ �� �������� �������"		<< endl
			<< "$3 - ������� ���� ������ (n ���.) ����� ������" << endl
			<< "$4 - �������� �������� ���� FIRST"				<< endl
			<< "$5 - ���������� �������� ���� FIRST"			<< endl
			<< "$6 - �������� �������� ���� SECOND"				<< endl
			<< "$7 - ���������� �������� ���� SECOND"			<< endl
			<< "$8 - ���������� ����� �����"					<< endl
			<< "$9 - ���������� ���������� �������"				<< endl
			<< "$10 - �������� [++]"							<< endl
			<< "$11 - �������� [--]"							<< endl
			<< "$12 - �������� [!]"								<< endl
			<< "$13 - �������� [+]"								<< endl
			<< "$14 - ����� �� ���������"				<< endl << endl;

		cout << "������� �����: ";
		getline(cin, readline);
		try
		{
			select_operation = stoi(readline);
		}
		catch (std::exception) 
		{
			cout << endl << "������ ��� �����" << endl;
			continue;
		}

		system("cls");
		switch (select_operation)
		{
		case 1:
			cout << money.get_info() << endl;
			break;

		case 2:
			cout << "������� ����� �������: ";
			cin >> value_operation;
			cout << (money.is_enough(value_operation) ? "������" : "�� ������") << endl;
			break;

		case 3:
			cout << "������� ��������� ������: ";
			cin >> value_operation;
			cout << "�������� ������: " << money.how_many_allow(value_operation) << " ��." << endl;
			break;

		case 4:
			cout << "�������� ���� FIRST: " << money.get_first() << endl;
			break;

		case 5:
			cout << "������� �������� FIRST: ";
			cin >> value_operation;
			money.set_first(value_operation);
			break;

		case 6:
			cout << "�������� ���� SECOND: " << money.get_second() << endl;
			break;

		case 7:
			cout << "������� �������� SECOND: ";
			cin >> value_operation;
			money.set_second(value_operation);
			break;

		case 8:
			cout << "����� ����� �����: " << money.get_sum() << endl;
			break;

		case 9:
			cout << "[0] - FIRST\t[1] - SECOND" << endl << "������� ������: ";
			cin >> value_operation;
			try 
			{
				cout << "�������� ��������: " << money[value_operation] << endl;
			}
			catch (std::exception error) 
			{
				cout << error.what() << endl;
			}
			break;

		case 10:
			cout << money.get_info() << endl;
			money++;
			cout << "��������� �������� [++]" << endl
				<< money.get_info() << endl;
			break;

		case 11:
			try 
			{
				cout << money.get_info() << endl;
				money--;
				cout << "��������� �������� [--]" << endl
					<< money.get_info() << endl;
			}
			catch (std::exception error) 
			{
				money++;
				cout << error.what() << endl;
			}
		
			break;

		case 12:
			cout << "��������� �������� [!]" << endl
				<< (!money ? "true" : "false") << endl;
			break;

		case 13:
			int value;
			cout << "������� �������� �������: ";
			cin >> value;
			money = money + value;
			break;

		case 14: return;
		default:
			cout << "������ �������� �����" << endl;
		}
		
		cout << endl;
		system("pause");
	}

}