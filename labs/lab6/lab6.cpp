#include "lab6.h"

///////////////////////////////////////--Point--/////////////////////////////////////////////

double lab6::Point::operator[](point_coordinate coordinate) const 
{
	switch (coordinate) 
	{
	case Point::x_coordinate: return this->position.x;
	case Point::y_coordinate: return this->position.y;
	case Point::z_coordinate: return this->position.z;
	default:
		throw exception("Невозможно выбрать координату вершины");
	}
}

double lab6::Point::calculate_distance(const Point& point)
{
	return sqrt(
		pow(this->position.x - point.position.x, 2) +
		pow(this->position.y - point.position.y, 2) +
		pow(this->position.z - point.position.z, 2)
	);
}

bool lab6::Point::move_to(Vector3d direction)
{
	this->position.x += direction.x;
	this->position.y += direction.y;
	this->position.z += direction.z;
	return true;
}

double lab6::Point::calculate_angle_between(Point A, Point B) 
{
	Vector3d A_dir(
		(*this)[Point::x_coordinate] - A[Point::x_coordinate],
		(*this)[Point::y_coordinate] - A[Point::y_coordinate],
		(*this)[Point::z_coordinate] - A[Point::z_coordinate]
	);

	Vector3d B_dir(
		(*this)[Point::x_coordinate] - B[Point::x_coordinate],
		(*this)[Point::y_coordinate] - B[Point::y_coordinate],
		(*this)[Point::z_coordinate] - B[Point::z_coordinate]
	);

	double angle = acos((A_dir.x * B_dir.x + A_dir.y * B_dir.y + A_dir.z * B_dir.z) /
		((*this).calculate_distance(A) * (*this).calculate_distance(B)));

	return angle;
}

///////////////////////////////////////--Shape2d--/////////////////////////////////////////////

double* lab6::Shape2d::calculate_angles(vector<Point> vertexs)
{
	double* angles = new double[vertexs.size()];

	angles[0] = vertexs[0].calculate_angle_between(vertexs[vertexs.size() - 1], vertexs[1]);
	
	for (int i = 1; i < vertexs.size() - 1; i++) 
		angles[i] = vertexs[i].calculate_angle_between(vertexs[i - 1], vertexs[i + 1]);

	angles[vertexs.size() - 1] = vertexs[vertexs.size() - 1]
		.calculate_angle_between(vertexs[vertexs.size() - 2], vertexs[0]);

	return angles;
}

double* lab6::Shape2d::calculate_edges(vector<Point> vertexs)
{
	double* edges = new double[vertexs.size()];

	edges[0] = this->vertexs[0].calculate_distance(vertexs[vertexs.size() - 1]);
	for (int i = 1; i < vertexs.size(); i++)
		edges[i] = this->vertexs[i - 1].calculate_distance(vertexs[i]);

	return edges;
}

lab6::Vector3d lab6::Shape2d::calculate_normal(vector<Point> vertexs)
{
	Vector3d dirA(
		vertexs[vertexs.size() - 1][Point::x_coordinate] - vertexs[0][Point::x_coordinate],
		vertexs[vertexs.size() - 1][Point::y_coordinate] - vertexs[0][Point::y_coordinate],
		vertexs[vertexs.size() - 1][Point::z_coordinate] - vertexs[0][Point::z_coordinate]
	), dirB(
		vertexs[1][Point::x_coordinate] - vertexs[0][Point::x_coordinate],
		vertexs[1][Point::y_coordinate] - vertexs[0][Point::y_coordinate],
		vertexs[1][Point::z_coordinate] - vertexs[0][Point::z_coordinate]
	);

	Vector3d normal = Vector3d(
		dirB.y * dirA.z - (dirB.z * dirA.y),
		dirB.x * dirA.z - (dirB.z * dirA.x),
		dirB.x * dirA.y - (dirB.y * dirA.x)
	);

	const double length = Point(Vector3d()).calculate_distance(normal);

	return Vector3d(normal.x / length, normal.y / length, normal.z / length);
}

double lab6::Shape2d::calculate_perimeter() const
{
	double result(0);
	for (int i = 0; i < this->get_vertex_count(); i++) result += this->edges[i];

	return result;
}

double lab6::Shape2d::get_angle(int index) const
{
	if (index < 0 || index >= this->vertexs.size())
		throw std::exception("Индекс вне доступного диапазона");
	return this->angles[index];
}

double lab6::Shape2d::get_egde(int index) const 
{
	if (index < 0 || index >= this->vertexs.size())
		throw std::exception("Индекс вне доступного диапазона");
	return this->edges[index];
}

lab6::Point lab6::Shape2d::operator[](int index) const
{
	if (index < 0 || index >= this->vertexs.size())
		throw std::exception("Индекс вне доступного диапазона");
	return vertexs[index];
}

bool lab6::Shape2d::move_to(Vector3d direction)
{
	for (auto& i : this->vertexs) i.move_to(direction);
	return true;
}

///////////////////////////////////////--Triangle--/////////////////////////////////////////////

double lab6::Triangle::calculate_area() const
{
	const double p = this->calculate_perimeter() / 2.;
	double result(p);
	for (int i = 0; i < this->get_vertex_count(); i++) result *= (p - this->get_egde(i));

	return sqrt(result);
}

lab6::Triangle lab6::Triangle::create_triangle(array<Point, 3> points)
{
	vector<Point> vertexs;
	for (const auto& i : points) vertexs.push_back(i);

	return Triangle(vertexs);
}

/////////////////////////////////////--Quadrangle--/////////////////////////////////////////////

double lab6::Quadrangle::calculate_area() const
{
	Vector3d A(
		(*this)[0][Point::x_coordinate] - (*this)[2][Point::x_coordinate],
		(*this)[0][Point::y_coordinate] - (*this)[2][Point::y_coordinate],
		(*this)[0][Point::z_coordinate] - (*this)[2][Point::z_coordinate]
	), B(
		(*this)[1][Point::x_coordinate] - (*this)[3][Point::x_coordinate],
		(*this)[1][Point::y_coordinate] - (*this)[3][Point::y_coordinate],
		(*this)[1][Point::z_coordinate] - (*this)[3][Point::z_coordinate]
	);

	const double angle = Point(Vector3d(0, 0, 0)).calculate_angle_between(Point(A), Point(B));

	const double S = (*this)[0].calculate_distance((*this)[2]) *
		(*this)[1].calculate_distance((*this)[3]) / 2. * sin(angle);

	return S;
}

lab6::Quadrangle lab6::Quadrangle::create_quadrangle(array<Point, 4> points)
{
	vector<Point> vertexs;
	for (const auto& i : points) vertexs.push_back(i);

	return Quadrangle(vertexs);
}

///////////////////////////////////////--Shape3d--/////////////////////////////////////////////

const lab6::Shape2d& lab6::Shape3d::operator[](int index) const
{
	if (index < 0 || index >= this->faces.size())
		throw std::exception("Индекс вне доступного диапазона");
	return *(this->faces[index]);
}

bool lab6::Shape3d::move_to(Vector3d direction)
{
	for (Shape2d* face : this->faces) (*face).move_to(direction);
	return true;
}

double lab6::Shape3d::calculate_fullarea() const
{
	double result(0);
	for (Shape2d* i : this->faces) result += i->calculate_area();

	return result;
}

/////////////////////////////////////--TrianglePrism--////////////////////////////////////////////

lab6::TrianglePrism lab6::TrianglePrism::create_prism_by_shape
	(array<Quadrangle, 3> sides, array<Triangle, 2> bases)
{
	vector<Shape2d*> faces;
	for (auto i : bases) faces.push_back(new Triangle(i));
	for (auto i : sides) faces.push_back(new Quadrangle(i));

	return TrianglePrism(faces);
}

lab6::TrianglePrism lab6::TrianglePrism::create_prism_by_param(
	Triangle base, Vector3d base_offset, double height)
{
	vector<Shape2d*> faces = { new Triangle(base) };
	Triangle* upper_base = new Triangle(base);
	Vector3d shift(
		base.get_normal().x * height + base_offset.x,
		base.get_normal().y * height + base_offset.y,
		base.get_normal().z * height + base_offset.z
	);

	if (upper_base->move_to(shift) != true)
		throw std::exception("Невозможно создать объект призмы");
	faces.push_back(upper_base);
	
	auto connect_vertexs = [&faces, &base, &upper_base]
		(int p1, int p2, int p3, int p4) -> void
	{
		Quadrangle side = Quadrangle::create_quadrangle(array<Point, 4>{
			base[p1], base[p2], (*upper_base)[p3], (*upper_base)[p4]
		});

		faces.push_back(new Quadrangle(side));
	};

	for (int i = 0; i < base.get_vertex_count() - 1; i++) connect_vertexs(i, i + 1, i + 1, i);
	connect_vertexs(base.get_vertex_count() - 1, 0, 0, base.get_vertex_count() - 1);

	return TrianglePrism(faces);
}

double lab6::TrianglePrism::calculate_size() const
{
	return this->height * this->get_lower_base().calculate_area();
}

double lab6::TrianglePrism::calculate_height() const
{
	Point base_point = this->get_upper_base()[0];
	Vector3d normal = this->get_lower_base().get_normal();

	double upper = fabs(
		normal.x * base_point[Point::x_coordinate] +
		normal.y * base_point[Point::y_coordinate] +
		normal.z * base_point[Point::z_coordinate]
	),lower = sqrt(
		pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)
	);

	return upper / lower;
}

double lab6::TrianglePrism::calculate_perimeter() const
{
	double P = this->get_lower_base().calculate_perimeter()
		+ this->get_upper_base().calculate_perimeter();

	for (int i = 0; i < this->get_lower_base().get_vertex_count(); i++) 
	{
		P += this->get_lower_base()[i].calculate_distance(this->get_upper_base()[i]);
	}

	return P;
}

////////////////////////////////////////--Testing--//////////////////////////////////////////////

void lab6::testing::test_point_class(void) 
{
	Point point(Vector3d(10, 10, 10));
	std::cout << "\t" << "Создание экземпляра точки с позицией (10, 10, 10)" << std::endl;

	std::cout << "\t" << "Расстояние до точки (20, 20, 20): " <<
		point.calculate_distance(Point(Vector3d(20, 20, 20))) << std::endl;

	std::cout << "\t" << "Предыдущее положение: x = " << point[Point::x_coordinate]
		<< "; y = " << point[Point::y_coordinate]
		<< "; z = " << point[Point::z_coordinate] << std::endl;

	std::cout << "\t" << "Вектор перемещения (x, y, z) -> (20, 20, -20)" << endl;

	point.move_to(Vector3d(20, 20, -20));

	std::cout << "\t" << "Текущее положение: x = " << point[Point::x_coordinate]
		<< "; y = " << point[Point::y_coordinate]
		<< "; z = " << point[Point::z_coordinate] << std::endl;

	std::cout << "\t" << "Угол между (0, 0, 0) и (10, 0, 0): " <<
		point.calculate_angle_between(Vector3d(0,0,0), Vector3d(10,0,0)) / M_PI * 180
		<< " (deg)" << std::endl;
}

void lab6::testing::test_triangle_class(void) 
{
	Triangle triangle = Triangle::create_triangle(array<Point, 3>{
		Point(Vector3d(10, 0, 0)), Point(Vector3d(0, 0, 0)), Point(Vector3d(0, 10, 0))
	});
	std::cout << "\t" << "Создание экземпляра треугольника с вершинами:" << std::endl
		<< "\t\t" << "(10, 0, 0), (0, 0, 0), (0, 10, 0)" << endl;

	std::cout << "\t" << "Количество вершин: " << triangle.get_vertex_count() << endl;
	cout << "\t" << "Вектор нормали: { " << triangle.get_normal().x << "; "
		<< triangle.get_normal().y << "; " << triangle.get_normal().z << " }" << endl;

	cout << "\t" << "Длина стороны с индексом [0]: " << triangle.get_egde(0) << endl;
	cout << "\t" << "Значение угла с индексом [0]: " << triangle.get_angle(0) / M_PI * 180 << endl;
	cout << "\t" << "Периметр: " << triangle.calculate_perimeter() << endl;
	cout << "\t" << "Площадь: " << triangle.calculate_area() << endl;

	cout << "\t" << "Положение вершины с индексом [0]" << "x: " << triangle[0][Point::x_coordinate]
		<< " y: " << triangle[0][Point::y_coordinate]
		<< " z: " << triangle[0][Point::z_coordinate] << endl;

	cout << "\t" << "Предыдущее положение: " << endl;
	for (int i = 0; i < triangle.get_vertex_count(); i++)
	{
		cout << "\t" << "x = " << triangle[i][Point::x_coordinate]
			<< "; y = " << triangle[i][Point::y_coordinate]
			<< "; z = " << triangle[i][Point::z_coordinate] << endl;
	}

	cout << "\t" << "Вектор перемещения (x, y, z) -> (10, 10, 10)" << endl;

	triangle.move_to(Vector3d(10, 10, 10));

	cout << "\t" << "Текущее положение: " << endl;
	for (int i = 0; i < triangle.get_vertex_count(); i++)
	{
		cout << "\t" << "x = " << triangle[i][Point::x_coordinate]
			<< "; y = " << triangle[i][Point::y_coordinate]
			<< "; z = " << triangle[i][Point::z_coordinate] << endl;
	}
}

void lab6::testing::test_triangle_prism_class(void) 
{
	auto prism = TrianglePrism::create_prism_by_param(
		Triangle::create_triangle(array<Point, 3>{
			Point(Vector3d(10, 0, 0)), Point(Vector3d(0, 0, 0)), Point(Vector3d(0, 10, 0))
		}), Vector3d(0, 0, 0), 10
	);
	std::cout << "\t" << "Создание экземпляра треугольной призмы с парамтерами:" << std::endl
		<< "\t\t" << "Вершины основания: (10, 0, 0), (0, 0, 0), (0, 10, 0)" << endl
		<< "\t\t" << "Высота: 10, Смещение верхнего основания: {0, 0, 0}" << endl;

	cout << "\t" << "Количество граней: " << prism.get_faces_count() << endl;
	cout << "\t" << "Предыдущее положение основания: " << endl;
	for (int i = 0; i < prism.get_lower_base().get_vertex_count(); i++)
	{
		cout << "\t" << "x = " << prism.get_lower_base()[i][Point::x_coordinate]
			<< "; y = " << prism.get_lower_base()[i][Point::y_coordinate]
			<< "; z = " << prism.get_lower_base()[i][Point::z_coordinate] << endl;
	}

	cout << "\t" << "Вектор перемещения (x, y, z) -> (10, 10, 10)" << endl;
	prism.move_to(Vector3d(10, 10, 10));

	cout << "\t" << "Текущее положение: " << endl;
	for (int i = 0; i < prism.get_lower_base().get_vertex_count(); i++)
	{
		cout << "\t" << "x = " << prism.get_lower_base()[i][Point::x_coordinate]
			<< "; y = " << prism.get_lower_base()[i][Point::y_coordinate]
			<< "; z = " << prism.get_lower_base()[i][Point::z_coordinate] << endl;
	}
	cout << "\t" << "Объем призмы: " << prism.calculate_size() << endl;
	cout << "\t" << "Площадь полной поверхности: " << prism.calculate_fullarea() << endl;
	cout << "\t" << "Полный периметр: " << prism.calculate_perimeter() << endl; \
	cout << "\t" << "Высота: " << prism.get_height() << endl;
}

void lab6::lab(void)
{
	cout << "Тестирование класса \"Point\"" << endl;
	testing::test_point_class();
	cout << endl << endl;

	cout << "Тестирование класса \"Triangle\"" << endl;
	testing::test_triangle_class();
	cout << endl << endl;

	cout << "Тестирование класса \"TrianglePrism\"" << endl;
	testing::test_triangle_prism_class();
	cout << endl << endl;
}
