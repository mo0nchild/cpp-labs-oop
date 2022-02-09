#pragma once
#include <iostream>
#include <vector>

namespace lab3 
{
	using namespace std;
	enum class direction { right_direction = 0, down_direction };

	using matrix_t = vector<vector<int>>;

	matrix_t create_matrix(int size) 
	{
		matrix_t result;
		for (int i = 0; i < size; i++)
		{
			result.push_back(vector<int>());
			for (int k = 0; k < size; k++) result[i].push_back(int(0));
		}

		return result;
	}

	matrix_t fill_matrix(matrix_t& matrix, int size)
	{
		int counter = 1;

		// ��������� �������� ��� ������� ������ (� = 0; � = 0)
		matrix[0][0] = counter++;

		// ��������� ���������� ����������� = �������
		direction dir(direction::right_direction);

		// ���������� �������
		for (int x = 0, y = 0; y != size - 1 || x != size - 1; ) 
		{
			// ��������: ���� ����������� = ������� ; � ������ ��������
			if (x < size - 1 && dir == direction::right_direction) 
			{
				// �������� ������� ������ � ��������� �������� ������
				matrix[y][++x] = counter++;

				// ����� �����������
				dir = direction::down_direction;
			}
			else if (y < size - 1 && dir == direction::down_direction) 
			{
				matrix[++y][x] = counter++;
				dir = direction::right_direction;
			}
			// ���� ���������� ������� �� ��������� �� �� ������ ����������� �������� ������� � ��������� (��������) ��� ��� 
			else 
			{
				if (dir == direction::down_direction) dir = direction::right_direction;
				else dir = direction::down_direction;
				continue;
			}

			// �������� ���� ������ ��������� �� ������� ������� : ����� ��� �����
			// ���� ������ �� ��� �������� ��� �������� �� ��������� ����� ���������� �� ��������� - ����� � ������
			// ����� - ���� � �����
			if (x == 0 || y == size - 1) 
			{
				// ����������� ������� �� ��������� ���� �� �� ������� � ������
				// ���������� ��������������� �������� ��� ������
				while (x < size - 1 && y > 0) matrix[--y][++x] = counter++;
			}
			else if (y == 0 || x == size - 1) 
			{
				while (y < size - 1 && x > 0) matrix[++y][--x] = counter++;
			}

		}

		return matrix;
	}

	void print_matrix(matrix_t& matrix)
	{
		for (vector<int> list : matrix) 
		{
			for (int i : list) cout << i << "\t";
			cout << endl << endl;
		}
	}

	namespace math_operation
	{
		int determinant(matrix_t matrix)
		{
			for (int i = 0; i < matrix.size(); i++) 
			{
				
			}
		}

		matrix_t inverse_matrix(matrix_t matrix)
		{

			

		}
	}

	bool run(void) 
	{
		bool error_state = true;
		int n = 0;

		try 
		{
			while (true) 
			{
				system("cls");

				cout << "������� ������ ������� (N x N) ��� 4 <= n <= 16: ";
				cin >> n;
				cout << endl;

				if (n >= 4 && n <= 16) break;
				else 
				{
					cout << "������� �������� ��������" << endl;
					system("pause");
				}
			}
			
			matrix_t matrix = create_matrix(n);
			matrix = fill_matrix(matrix, n);

			print_matrix(matrix);
		}
		catch (...) 
		{
			error_state = false;
		}

		return error_state;
	}

	void lab(void) 
	{
		bool error_state = run();
	}

}