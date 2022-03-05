#include "lab7.h"

using namespace lab7;

void lab7::task1::run(void) 
{
	Expression* e1 = new Number(1.234);
	Expression* e2 = new Number(-1.234);
	Expression* e3 = new BinaryOperation(e1, BinaryOperation::DIV, e2);

	cout << e3->evaluate() << endl;
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
	cout << callAbs->evaluate() << endl;
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

			if (x == width / 2 || y == height / 2) cout << "\' ";
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
	Shape* circle2 = new Circle(Vector3d(13, 10, 0), "circle2", 4);
	Shape* sphere1 = new Sphere(Vector3d(-9, 10, 0), "sphere1", 4);
	Shape* sphere2 = new Sphere(Vector3d(-15, 0, 0), "sphere2", 6);

	Point* point = new Point(Vector3d(5, 5, 0), "point1");

	Renderer renderer(vector<Shape*>{circle1, circle2, sphere1, sphere2, point}, 30, 30);

	renderer.get_info();
	renderer.update()->render();

}

void lab7::lab(void) 
{
	task3::run();
}
