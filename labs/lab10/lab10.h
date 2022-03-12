#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <chrono>
#include <thread>
#include <mutex>
#include <functional>
#include <windows.h>

using namespace std;

#define MAX_STEP 3
#define MIN_STEP -2

#define RANDOM_SIZE 7

namespace lab10 
{

	struct Vector2d 
	{
		double x, y;
		Vector2d(double x = 0, double y = 0): x(x), y(y) { }
	};

	enum class CoolPriority 
	{
		HIGHEST = THREAD_PRIORITY_HIGHEST,
		ABOVE_NORMAL = THREAD_PRIORITY_ABOVE_NORMAL,
		NORMAL = THREAD_PRIORITY_NORMAL,
		BELOW_NORMAL = THREAD_PRIORITY_BELOW_NORMAL,
		LOWEST = THREAD_PRIORITY_LOWEST
	};

	class Ball 
	{
		Vector2d position;
		const string name;
		const uint16_t id;
		bool is_active;

		static uint16_t current_id;
		
	public:
		explicit Ball(Vector2d position, string name)
			: position(position), name(name), id(current_id++), is_active(true)
		{ }

		~Ball() { }

		Vector2d get_position(void) const noexcept { return this->position; }
		string get_name(void) const noexcept { return this->name; }
		uint16_t get_id(void) const  noexcept { return this->id; }

		void set_active(bool value) noexcept { this->is_active = value; }
		bool get_active(void) const noexcept { return this->is_active; }

		void move_to(Vector2d direction) noexcept
		{
			this->position.x += direction.x;
			this->position.y += direction.y;
		}
	};

	class Renderer 
	{
		vector<Ball*> balls;
		const double border_x;
		pair<int, int> render_size;

		void calculate_motion(Ball* ball, mutex& mute, vector<int> rand_values);
	public:

		Renderer(void) = delete;
		explicit Renderer(vector<Ball*> balls, double border_x, pair<int, int> size)
			: balls(balls), border_x(border_x)
		{ 
			if (size.first < 10 || size.second < 10) throw exception("Малый размер");
			this->render_size = size;
		}

		~Renderer() { for (auto i : balls) delete i; }

		void begin(vector<CoolPriority> priority);
	};

	void lab(void);
}