#pragma once
#include <iostream>
#include <vector>

namespace lab3 // https://youtu.be/IKJHMhtMnR0
{
	using namespace std;
	enum class direction { right_direction = 0, down_direction };

	using matrix_t = vector<vector<double>>;

	matrix_t create_matrix(int size) 
	{
		matrix_t result;
		for (int i = 0; i < size; i++)
		{
			result.push_back(vector<double>());
			for (int k = 0; k < size; k++) result[i].push_back(double(0));
		}

		return result;
	}

	matrix_t fill_matrix(matrix_t& matrix, int size)
	{
		double counter = 1;

		// установка значения для нулевой клетки (х = 0; у = 0)
		matrix[0][0] = counter++;

		// установка начального навравления = направо
		direction dir(direction::right_direction);

		// заполнение матрицы
		for (int x = 0, y = 0; y != size - 1 || x != size - 1; ) 
		{
			// проверка: если направление = направо ; и справа свободно
			if (x < size - 1 && dir == direction::right_direction) 
			{
				// смещение курсора вправо и установка значения клетки
				matrix[y][++x] = counter++;

				// смена направления
				dir = direction::down_direction;
			}
			else if (y < size - 1 && dir == direction::down_direction) 
			{
				matrix[++y][x] = counter++;
				dir = direction::right_direction;
			}
			// если предыдущие условия не сработали то мы меняем направление движения курсора и повторяем (итерацию) еще раз 
			else 
			{
				if (dir == direction::down_direction) dir = direction::right_direction;
				else dir = direction::down_direction;
				continue;
			}

			// проверка если курсор находится на границе матрицы : слево или снизу
			// если истина то это означает что движение по диагонали будет направлено по диагонали - вверх и вправо
			// иначе - вниз и влево
			if (x == 0 || y == size - 1) 
			{
				// перемещение курсора по диагонали пока он не упрется в стенку
				// паралельно устанавливаются значения для клеток
				while (x < size - 1 && y > 0) matrix[--y][++x] = counter++;
			}
			else if (y == 0 || x == size - 1) 
			{
				while (y < size - 1 && x > 0) matrix[++y][--x] = counter++;
			}

		}

		return matrix;
	}

	void print_matrix(matrix_t matrix)
	{
		for (vector<double> list : matrix)
		{
			for (double i : list) cout << i << "\t";
			cout << endl << endl;
		}
	}

	namespace math_operation
	{
		matrix_t transpose(matrix_t matrix)
		{
			matrix_t result = create_matrix(matrix.size());

			for (int y = 0; y < matrix.size(); y++)
			{
				for (int x = 0; x < matrix.size(); x++) result[y][x] = matrix[x][y];
			}
			return result;
		}
		
		matrix_t minor_matrix(matrix_t matrix, int x_rm, int y_rm)
		{
			matrix_t result = create_matrix(matrix.size() - 1);
			for (int y = 0, result_y = 0; y < matrix.size(); y++)
			{
				if (y == y_rm) continue;

				for (int x = 0, result_x = 0; x < matrix.size(); x++)
				{
					if (x == x_rm) continue;
					result[result_y][result_x++] = matrix[y][x];
				}

				result_y++;
			}
			return result;
		}

		double determinant(matrix_t matrix)
		{
			// терминальное условие: если минор матрицы 2-ого порядка
			if (matrix.size() <= 2)
			{
				return matrix[0][0] * matrix[1][1] - (matrix[0][1] * matrix[1][0]);
			}

			double result = 0;
			for (int i = 0; i < matrix.size(); i++) 
			{
				// находим минор 
				matrix_t new_matrix = minor_matrix(matrix, i, 0);
				result += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(new_matrix);
			}
			return result;
		}

		matrix_t inverse_matrix(matrix_t matrix)
		{
			double det = determinant(matrix);
			if (det == 0) 
			{
				cout << "Определитель равен нулю - невозможно составить обратную матрицу" << endl;
				throw std::exception("det = 0");
			}	
			
			matrix_t result = create_matrix(matrix.size());
			matrix = transpose(matrix);

			for (int y = 0; y < result.size(); y++)
			{
				for (int x = 0; x < result.size(); x++)
				{
					result[y][x] = pow(-1, x + y) * determinant(minor_matrix(matrix, x, y)) * (1./ det);
				}

			}

			return result;

		}

		matrix_t multiply_matrix(matrix_t matrix1, matrix_t matrix2)
		{

			matrix_t result = create_matrix(matrix1.size());

			for (int y = 0; y < result.size(); y++) 
			{
				for (int x = 0; x < result.size(); x++) 
				{

					for (int i = 0; i < result.size(); i++)
					{
						result[y][x] += matrix1[y][i] * matrix2[i][x];
					}

				}
			}
			return result;
		}
	}

	bool run(void) 
	{
		bool error_state = true;
		int n = 0;

		try 
		{
			cout << fixed;
			cout.precision(2);
			while (true) 
			{
				system("cls");//Определитель отличен от нуля, следовательно, матрица является невырожденной и для нее можно найти обратную матрицу.
				 
				cout << "Введите размер матрицы (N x N) где 4 <= n <= 16: ";
				cin >> n;
				cout << endl;

				if (n >= 4 && n <= 16) break;
				else 
				{
					cout << "Введены неверные значения" << endl;
					system("pause");
				}
			}
			
			matrix_t matrix = create_matrix(n), inverse;
			matrix = fill_matrix(matrix, n);
			inverse = math_operation::inverse_matrix(matrix);

			cout << endl << endl;

			print_matrix(matrix);
			cout << endl << endl;

			print_matrix(inverse);
			cout << endl << endl;

			matrix_t result = math_operation::multiply_matrix(matrix, inverse);
			print_matrix(result);


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