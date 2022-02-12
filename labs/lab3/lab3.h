#pragma once
#include <iostream>
#include <vector>

namespace lab3 //  https://youtu.be/IKJHMhtMnR0
{
	using namespace std;

	enum class direction { right_direction = 0, down_direction };
	using matrix_t = vector<vector<double>>;
	
	struct SquareMatrix 
	{
	private:
		matrix_t matrix;

	public:
		SquareMatrix(int size);

		// методы доступа
		int size() { return matrix.size(); }
		double& get_cell(int x, int y) 
		{
			if ((x < matrix.size() && x >= 0) && (y < matrix.size() && y >= 0))
			{
				return matrix[y][x];
			}
			throw std::out_of_range("indexs_out_of_range");
		}

		static void print_matrix(SquareMatrix& matrix);

	};

	SquareMatrix fill_matrix(SquareMatrix& matrix);

	namespace math_operation
	{
		SquareMatrix transpose(SquareMatrix& matrix);
		
		SquareMatrix minor_matrix(SquareMatrix matrix, int x_rm, int y_rm);

		double determinant(SquareMatrix matrix);

		SquareMatrix* inverse_matrix(SquareMatrix matrix);

		SquareMatrix* multiply_matrix(SquareMatrix matrix1, SquareMatrix matrix2);
	}

	bool run(void);

	void lab(void);

}