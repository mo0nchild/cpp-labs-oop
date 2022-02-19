#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace lab5 
{
	using namespace std;
	class Money
	{
		// first - ������� ������, second - ���-�� �����
		int first, second;
	public:
		Money(int first, int second)
			: first(first), second(second)
		{ }

		std::string get_info(void);
		bool is_enough(int purchase);
		int how_many_allow(int purchase);

		int get_sum(void) { return first * second; }

		void set_second(int value) { second = (value >= 0) ? value : 0; }
		int get_second(void) { return second; }

		void set_first(int value) { first = (value >= 0) ? value : 0; }
		int get_first(void) { return first; }

		int& operator [](int index);

		// ���� � ���, ��� ���� C++ ���������� ��������� ���������� (��� ���������� ��������) 
		// ��� ���������� ������ ��������. ���� ��������� ������������� �������� ������������ ������ 
		// � ����� �����: �������� ������ �������� ���������� ����������/���������� �� ������ �������.

		// ������ ��������
		Money operator ++(int);
		Money operator --(int);

		// ������ �������
		Money& operator++();
		Money& operator--();

		bool operator!();
		Money& operator+( int value);
	};

	void lab(void);
}