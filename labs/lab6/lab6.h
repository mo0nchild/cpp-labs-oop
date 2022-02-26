#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <sstream>

# define M_PI 3.14159265358979323846
#include <cmath>

// Точка -> Треугольник -> Треугольная призма 
// (отношения будут реализованы через композицию)

namespace lab6 
{
	using namespace std;
	
	struct Vector3d 
	{ 
		double x, y, z; 
		Vector3d(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z)
		{ }
	};

	class IMoveble 
	{
	public:
		virtual bool move_to(Vector3d direction) = 0;
	};

	class Point: public IMoveble
	{
		Vector3d position;
	public:
		Point(Vector3d position) : position(position)
		{ }
		
		enum point_coordinate { x_coordinate, y_coordinate, z_coordinate };

		double calculate_distance(const Point& point);
		bool move_to(Vector3d direction) override;
		double calculate_angle_between(Point A, Point B);

		double operator[](point_coordinate coordinate) const;
	};

	class Shape2d: public IMoveble
	{
		double *angles, *edges;
		Vector3d normal;
		vector<Point> vertexs;

	protected:
		
		double* calculate_angles(vector<Point> vertexs);
		double* calculate_edges(vector<Point> vertexs);
		Vector3d calculate_normal(vector<Point> vertexs);

	public:
		Shape2d(vector<Point> vertexs) : vertexs(vertexs) 
		{ 
			this->angles = calculate_angles(vertexs); 
			this->edges = calculate_edges(vertexs);
			this->normal = calculate_normal(vertexs);
		}

		~Shape2d() { delete[] angles; delete[] edges; }

		int get_vertex_count() const { return vertexs.size(); }
		Vector3d get_normal() const { return normal; }

		double get_egde(int index) const;
		double get_angle(int index) const;

		Point operator[](int index) const;

		virtual double calculate_perimeter() const;
		virtual double calculate_area() const = 0;

		bool move_to(Vector3d direction) override;
	};

	class Triangle: public Shape2d
	{
	protected:
		Triangle(vector<Point> vertexs) : Shape2d(vertexs)
		{ }
	public:

		static Triangle create_triangle(array<Point, 3> points);
		double calculate_area() const override;
	};

	class Quadrangle : public Shape2d 
	{
	protected:
		Quadrangle(vector<Point> vertexs) : Shape2d(vertexs)
		{ }

	public:
		static Quadrangle create_quadrangle(array<Point, 4> points);
		// Площадь произвольного четырехугольника можно найти перемножив 
		// диагонали данного четырехугольника, полученный результат разделить 
		// на 2 и умножить результат на синус угла.
		double calculate_area() const override;
	};

	class Shape3d: public IMoveble
	{
		vector<Shape2d*> faces;	
	public:
		Shape3d(vector<Shape2d*> faces): faces(faces)
		{ }

		~Shape3d() 
		{
			for (int i = 0; i < faces.size(); i++) 
			{
				delete faces[i];
			}
		}

		int get_faces_count() const { return faces.size(); }
		bool move_to(Vector3d direction) override;

		virtual double calculate_size() const = 0;
		virtual double calculate_perimeter() const = 0;
		virtual double calculate_fullarea() const;

		const Shape2d& operator[](int index) const;

	};

	class TrianglePrism : public Shape3d 
	{
		double height;
	protected:
		double calculate_height() const;
		TrianglePrism(vector<Shape2d*> faces) : Shape3d(faces)
		{ 
			this->height = calculate_height(); 
		}
	public:
		
		const Shape2d& get_upper_base() const { return (*this)[1]; }
		const Shape2d& get_lower_base() const { return (*this)[0]; }
		const Shape2d& get_side(int index) const { return (*this)[index + 2]; };

		static TrianglePrism* create_prism_by_shape(
			array<Quadrangle, 3> sides, array<Triangle, 2> bases);

		static TrianglePrism* create_prism_by_param(
			Triangle base, Vector3d base_offset, double height);

		const double get_height() const { return height; }
		double calculate_size() const override;
		double calculate_perimeter() const override;
	};

	void lab(void);
}