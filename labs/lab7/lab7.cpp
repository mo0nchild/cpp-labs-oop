#include "lab7.h"

using namespace lab7;

void lab7::task1::run(void) 
{
	Expression* e1 = new Number(1.234);
	Expression* e2 = new Number(-1.234);
	Expression* e3 = new BinaryOperation(e1, BinaryOperation::DIV, e2);

	cout << "Результат: " << e3->evaluate() << endl;
	delete e3;
}

void lab7::task2::run(void)
{
	Expression* n32 = new Number(32.0);
	Expression* n16 = new Number(16.0);
	Expression* minus = new BinaryOperation(n32, BinaryOperation::MINUS, n16);
	Expression* callSqrt = new FunctionCall("sqrt", minus);
	Expression* n2 = new Number(2.0);
	Expression* mult = new BinaryOperation(n2, BinaryOperation::MUL, callSqrt);
	Expression* callAbs = new FunctionCall("abs", mult);
	cout << "Результат: " << callAbs->evaluate() << endl;
	delete callAbs;

}

vector <task3::RenderStripe> task3::Renderer::update_layers_table(vector<Shape*> shapes)
{
	vector<RenderStripe> table;

	for (int y = height / 2; y > -(height / 2 - 1); y--)
	{
		table.push_back(RenderStripe{});

		for (auto shape : shapes)
		{
			double y_begin = shape->draw_shape().frame_position.y,
				y_end = y_begin - shape->draw_shape().height;

			if (y <= y_begin && y > y_end)
			{
				ShapeLayer layer = shape->draw_shape().layers[abs(y - y_begin)];
				const int render_system_y = height - (y + height / 2);

				table[render_system_y].insert(pair<int, ShapeLayer>(
					shape->draw_shape().frame_position.x, layer
					));
			}
		}
	}

	return table;
}

task3::Renderer* task3::Renderer::render(void) 
{
	for (int y = 0; y < height - 1; y++)
	{
		string current_layer = " ";
		int current_layer_process = 0;

		for (int x = 0; x < width; x++)
		{
			int system_x = int(x - width / 2),
				system_y = int(height / 2 - y);

			if (x == int(width / 2) || y == int(height / 2)) cout << "\' ";
			else if (y == height / 2 + 1 && x % 2 == 0 && abs(system_x) < XOY_NUMBER_RANGE)
			{
				cout << abs(system_x) << " ";
			}
			else if (x == width / 2 - 1 && y % 2 == 0 && abs(system_y) < XOY_NUMBER_RANGE)
			{
				cout << abs(system_y) << " ";
			}
			else
			{
				const RenderStripe& current_stripe = sorted_layers[y];
				if (current_stripe.find(system_x) != sorted_layers[y].end())
				{
					current_layer = current_stripe.at(system_x);
					current_layer_process = 0;
				}
				else if (current_layer_process < current_layer.size())
				{
					cout << current_layer[current_layer_process] << " ";
					current_layer_process++;
				}
				else cout << "  ";
			}
		}

		cout << endl;
	}

	return this;
}

task3::RenderLayer task3::Circle::draw_shape(void) const
{
	stringstream buffer;
	ShapeLayers layers;

	Vector3d frame_position = Vector3d(center.x - radius, center.y + radius);

	for (int y = 0; y <= 2 * radius; y++)
	{
		double delta = cos(asin((radius - y) / radius)) * radius;

		for (int x = 0; x < 2 * radius; x++)
		{
			if (x == (int)(radius - delta) || x == (int)(delta + radius))buffer << "#";
			else if (x < delta + radius) buffer << " ";
		}

		layers.push_back(buffer.str());
		buffer.str(string());
	}

	return RenderLayer(radius * 2, radius * 2 + 1, frame_position, layers);
}

task3::RenderLayer task3::Sphere::draw_shape(void) const
{
	stringstream buffer;
	ShapeLayers layers;

	Vector3d frame_position = Vector3d(center.x - radius, center.y + radius);

	for (int y = 0; y <= 2 * radius; y++)
	{
		double delta = cos(asin((radius - y) / radius)) * radius;

		for (int x = 0; x < 2 * radius; x++)
		{
			if (x >= (int)(radius - delta) && x <= (int)(delta + radius))buffer << "@";
			else if (x < delta + radius) buffer << " ";
		}

		layers.push_back(buffer.str());
		buffer.str(string());
	}

	return RenderLayer(radius * 2, radius * 2 + 1, frame_position, layers);
}

void lab7::task3::run(void)
{

	Shape* circle1 = new Circle(Vector3d(10, 10, 0), "circle1", 4);
	Sphere* sphere1 = new Sphere(Vector3d(-9, 10, 0), "sphere1", 4);
	Shape* point = new Point(Vector3d(8, -7, 0), "point1");

	cout << circle1->get_name() << " - периметр = " << circle1->calculate_perimeter() << endl;
	cout << circle1->get_name() << " - площадь = " << circle1->calculate_area() << endl << endl;

	cout << point->get_name() << " - периметр = " << point->calculate_perimeter() << endl;
	cout << point->get_name() << " - площадь = " << point->calculate_area() << endl << endl;

	cout << sphere1->get_name() << " - периметр = " << sphere1->calculate_perimeter() << endl;
	cout << sphere1->get_name() << " - площадь = " << sphere1->calculate_area() << endl;
	cout << sphere1->get_name() << " - объем = " << sphere1->calculate_size() << endl;

	Renderer renderer(vector<Shape*>{circle1, sphere1, point}, 49, 50);

	renderer.get_info();
	renderer.update()->render();

}

void lab7::lab(void) 
{
	task3::run();
}
