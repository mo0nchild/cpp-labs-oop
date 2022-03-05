#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include <map>

#define M_PI 3.14159265358979323846
#define XOY_NUMBER_RANGE 10
#define MIN_RADIUS 4

using namespace std;

namespace lab7 
{
	namespace task1 
	{

		struct Expression
		{
			// здесь должен быть ваш код
			virtual double evaluate() const = 0;
			virtual ~Expression() { };
		};

		struct Number : Expression
		{
			Number(double value) : value_(value) {}
			double value() const { return value_; }
			double evaluate() const { return value_; }
		private:
			double value_;
		};

		struct BinaryOperation : Expression
		{
			enum {
				PLUS = '+',
				MINUS = '-',
				DIV = '/',
				MUL = '*'
			};

			BinaryOperation(Expression const* left, int op,
				Expression const* right) :left_(left), op_(op), right_(right)
			{
				assert(left_ && right_);
			}
			~BinaryOperation()
			{
				delete left_;
				delete right_;
			}
			Expression const* left() const { return left_; }
			Expression const* right() const { return right_; }
			int operation() const { return op_; }

			double evaluate() const
			{
				double left = left_->evaluate();
				double right = right_->evaluate();
				switch (op_)
				{
				case PLUS: return left + right;
				case MINUS: return left - right;
				case DIV: return left / right;
				case MUL: return left * right;
				}
				assert(0);
				return 0.0;
			}
		private:
			Expression const* left_;
			Expression const* right_;
			int op_;
		};

		void run(void);

	}

	namespace task2
	{
		using task1::BinaryOperation;
		using task1::Expression;
		using task1::Number;

		struct FunctionCall : Expression
		{

			/**
			* @name – это имя функции, возможные варианты
			* "sqrt" и "abs".
			*
			* Объекты, std::string можно

			* сравнивать с C-строками используя
			* обычный синтаксис ==.
			*
			* @arg – выражение-аргумент функции
			*/

			FunctionCall(const string& name, const Expression* arg): _name(name), _arg(arg)
			{
				//реализация
				assert(name == "abs" || name == "sqrt");
			}
			// реализуйте оставшиеся методы из интерфейса структуры Expression и не забудьте
			// удалить arg_, как это сделано в классе BinaryOperation. Также реализуйте предложенные ниже методы

			double evaluate() const override
			{
				if (_name == "sqrt") return sqrt(_arg->evaluate());
				else if (_name == "abs") return fabs(_arg->evaluate());

				else throw exception("Неизвестная функция");
			};

			std::string const& name() const { return this->_name; }
			Expression const* arg() const { return this->_arg; }

			~FunctionCall() 
			{ 
				cout << "Удаление функции " << _name << endl;
				delete this->_arg; 
			}

		private:
			//а тут должны быть поля для FunctionCall
			const string _name;
			const Expression* _arg;
			
		};

		void run(void);
	}

	namespace task3
	{
		struct Vector3d 
		{ 
			double x, y, z; 
			Vector3d(double x = 0, double y = 0, double z = 0)
				: x(x), y(y), z(z) 
			{ }
		};

		using ShapeLayer = string;
		using ShapeLayers = vector<ShapeLayer>;
		using RenderStripe = map<int, ShapeLayer>;

		struct RenderLayer 
		{
			const double width, height;
			const Vector3d frame_position;
			const ShapeLayers layers;

			RenderLayer(double w, double h, Vector3d pos, ShapeLayers layers)
				: width(w), height(h), frame_position(pos), layers(layers)
			{ }
		};

		struct Shape
		{
			explicit Shape(Vector3d center, string name) 
				: center(center), name(name), id(current_id++)
			{ }
			virtual ~Shape(void) { }

			virtual Shape* move_to(Vector3d direction) 
			{
				center.x += direction.x;
				center.y += direction.y;
				center.z += direction.z;

				return this;
			}
			virtual double calculate_area(void) const = 0;
			virtual double calculate_perimeter(void) const = 0;

			virtual RenderLayer draw_shape(void) const = 0;
			virtual Shape* clone(void) const = 0;

			Vector3d get_position(void) const noexcept { return this->center; }
			string get_name(void) const noexcept { return this->name; }
			uint16_t get_id(void) const noexcept { return this->id; }

			virtual string get_info(void) const
			{
				return  + "id: " + to_string(id) + "\tname: " + name + "\nx: " + to_string(center.x)
					+ "\ty: " + to_string(center.y)
					+ "\tz: " + to_string(center.z);
			}

		protected:
			Vector3d center;
			string name;
			uint16_t id;
		private:
			static uint16_t current_id;
		};

		class Renderer
		{
			vector<Shape*> shapes;
			vector<RenderStripe> sorted_layers;
			double width, height;

			vector<RenderStripe> update_layers_table(vector<Shape*> shapes);

		public:

			Renderer(const Renderer& rend) = delete;
			Renderer() = delete;

			explicit Renderer(vector<Shape*> shapes, double h, double w)
				: shapes(shapes), height(h), width(w)
			{
				this->sorted_layers = update_layers_table(shapes);
			}

			Renderer(Shape* shapes, double h, double w)
				: height(h), width(w)
			{ 
				this->shapes.push_back(shapes);
				this->sorted_layers = update_layers_table(this->shapes);
			}

			virtual ~Renderer(void) { for (Shape* i : shapes) delete i; }

			void get_info(void) const noexcept 
			{
				for (auto i : shapes) cout << i->get_info() << endl;
			}

			Renderer* update(void) 
			{ 
				this->sorted_layers = update_layers_table(this->shapes); 
				return this;
			}

			Renderer* render(void);

			Renderer* add_shape(vector<Shape*> shapes)
			{
				for (auto i : shapes) this->shapes.push_back(i);
				return this;
			}

			Renderer* add_shape(Shape* shapes)
			{
				this->shapes.push_back(shapes);
				return this;
			}
		};

		class Point : public Shape
		{
			const double h = 1, w = 1;
		public:
			explicit Point(Vector3d center, string name): Shape(center, name) { }

			double calculate_area(void) const override { return M_PI * pow(h / 2. , 2); }
			double calculate_perimeter(void) const override { return M_PI * h; }

			RenderLayer draw_shape(void) const override
			{
				return RenderLayer(1, 1, center, ShapeLayers{"o"});
			}
			
			Shape* clone(void) const override { return new Point(*this); }
		};

		class Circle : public Shape
		{
			double radius;
		public:
			explicit Circle(Vector3d center, string name, double radius = MIN_RADIUS)
				: radius(radius), Shape(center, name) 
			{
				if (radius < MIN_RADIUS) throw exception("Недопустимое значение радиуса");
			}

			double calculate_area(void) const override { return M_PI * pow(radius, 2); }
			double calculate_perimeter(void) const override { return 2. * M_PI * radius; }

			double get_radius(void) const { return this->radius; }

			RenderLayer draw_shape(void) const override;

			Shape* clone(void) const override { return new Circle(*this); }
		};

		class Sphere : public Shape 
		{
			double radius;
		public:
			explicit Sphere(Vector3d center, string name, double radius = MIN_RADIUS)
				: radius(radius), Shape(center, name)
			{
				if (radius < MIN_RADIUS) throw exception("Недопустимое значение радиуса");
			}

			RenderLayer draw_shape(void) const override;

			double get_radius(void) const { return this->radius; }

			double calculate_size(void) const { return 4. / 3. * M_PI * pow(radius, 3); }

			double calculate_area(void) const override { return 4. * M_PI * pow(radius, 2); }
			double calculate_perimeter(void) const override { return 2. * M_PI * radius; }

			Circle* get_circle_projection(void) 
			{
				return new Circle(center, name, radius);
			}

			Shape* clone(void) const override { return new Sphere(*this); }
		};

		void run(void);
	}

	void lab(void);
}