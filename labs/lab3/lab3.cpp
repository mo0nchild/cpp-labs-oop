#include "lab3.h"
using namespace lab3;

SquareMatrix::SquareMatrix(int size)
{
	for (int i = 0; i < size; i++)
	{
		matrix.push_back(vector<double>());
		for (int k = 0; k < size; k++) matrix[i].push_back(double(0));
	}
}

void SquareMatrix::print_matrix(SquareMatrix& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int k = 0; k < matrix.size(); k++) cout << matrix.get_cell(k, i) << "\t";
		cout << endl << endl;
	}
}

SquareMatrix math_operation::transpose(SquareMatrix& matrix)
{
	SquareMatrix result(matrix.size());

	for (int y = 0; y < matrix.size(); y++)
	{
		for (int x = 0; x < matrix.size(); x++) result.get_cell(x, y) = matrix.get_cell(y, x);
	}
	return result;
}

SquareMatrix math_operation::minor_matrix(SquareMatrix matrix, int x_rm, int y_rm)
{
	SquareMatrix result(matrix.size() - 1);
	for (int y = 0, result_y = 0; y < matrix.size(); y++)
	{
		if (y == y_rm) continue;
		for (int x = 0, result_x = 0; x < matrix.size(); x++)
		{
			if (x == x_rm) continue;

			result.get_cell(result_x++, result_y) = matrix.get_cell(x, y);
		}
		result_y++;
	}
	return result;
}

double math_operation::determinant(SquareMatrix matrix)
{
	// терминальное условие: если минор матрицы 2-ого порядка
	if (matrix.size() <= 2)
	{
		return matrix.get_cell(0, 0) * matrix.get_cell(1, 1)
			- (matrix.get_cell(1, 0) * matrix.get_cell(0, 1));
	}

	double result = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		// находим минор 
		SquareMatrix new_matrix = minor_matrix(matrix, i, 0);
		result += (i % 2 == 0 ? 1 : -1) * matrix.get_cell(i, 0) * determinant(new_matrix);
	}
	return result;
}

SquareMatrix* math_operation::inverse_matrix(SquareMatrix matrix)
{
	double det = determinant(matrix);
	if (det == 0) return NULL;

	SquareMatrix* result = new SquareMatrix(matrix.size());
	matrix = transpose(matrix);

	for (int y = 0; y < result->size(); y++)
	{
		for (int x = 0; x < result->size(); x++)
		{
			result->get_cell(x, y) = pow(-1, x + y) * determinant(minor_matrix(matrix, x, y)) * (1. / det);
		}

	}

	return result;

}

SquareMatrix* math_operation::multiply_matrix(SquareMatrix matrix1, SquareMatrix matrix2)
{
	if (matrix1.size() != matrix2.size()) return NULL;
	SquareMatrix* result = new SquareMatrix(matrix1.size());

	// лямда-фукнция для вычисления значения клетки при перемножении столбцов и строк
	// захватываем перемножаемые матрицы в анонимном методе
	auto line_operation = [&matrix1, &matrix2](int x, int y)
	{
		double cell_value = 0;
		for (int i = 0; i < matrix1.size(); i++)
		{
			cell_value += (matrix1.get_cell(i, y) * matrix2.get_cell(x, i));
		}
		return cell_value;
	};

	for (int y = 0; y < result->size(); y++)
	{
		for (int x = 0; x < result->size(); x++)
		{
			result->get_cell(x, y) = line_operation(x, y);
		}
	}
	return result;
}
	
SquareMatrix lab3::fill_matrix(SquareMatrix& matrix, int size)
{
	double counter = 1;

	// установка значения для нулевой клетки (х = 0; у = 0)
	matrix.get_cell(0, 0) = counter++;
	// установка начального навравления = направо
	direction dir(direction::right_direction);

	// заполнение матрицы
	for (int x = 0, y = 0; y != size - 1 || x != size - 1; )
	{
		// проверка: если направление = направо ; и справа свободно
		if (x < size - 1 && dir == direction::right_direction)
		{
			// смещение курсора вправо и установка значения клетки
			matrix.get_cell(++x, y) = counter++;

			// смена направления
			dir = direction::down_direction;
		}
		else if (y < size - 1 && dir == direction::down_direction)
		{
			matrix.get_cell(x, ++y) = counter++;
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
			while (x < size - 1 && y > 0) matrix.get_cell(++x, --y) = counter++;
		}
		else if (y == 0 || x == size - 1)
		{
			while (y < size - 1 && x > 0) matrix.get_cell(--x, ++y) = counter++;
		}

	}

	return matrix;
}

bool lab3::run(void)
{
	int n = 0;
	bool error_state = true;

	cout << fixed;
	cout.precision(2);

	try
	{
		while (true)
		{
			system("cls");

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

		SquareMatrix matrix(n), * inverse, * result;
		matrix = fill_matrix(matrix, n);

		// определитель отличен от нуля, следовательно, матрица является невырожденной и для нее можно найти обратную матрицу.
		if ((inverse = math_operation::inverse_matrix(matrix)) == NULL)
		{
			cout << "Исходная матрица является вырожденной - нельзя получить обратную матрицу" << endl;
			throw std::exception("det = 0");
		}

		cout << "Сгенерированная матрица: " << endl << endl;
		SquareMatrix::print_matrix(matrix);

		cout << endl << endl << "Обратная матрица: " << endl << endl;
		SquareMatrix::print_matrix(*inverse);
		cout << endl << endl;

		if ((result = math_operation::multiply_matrix(matrix, *inverse)) == NULL)
		{
			cout << "Матрицы нельзя перемножить" << endl;
			throw std::exception("cannot multiply");
		}

		cout << endl << endl 
			<< "Полученная путем перемножения сгенерированной и обратной,\nЕдиничная матрица: "
			<< endl << endl;
		SquareMatrix::print_matrix(*result);

		delete inverse, result;
	}
	catch (...)
	{
		error_state = false;
	}

	return error_state;
}

void lab3::lab(void)
{
	bool error_state = run();
}

