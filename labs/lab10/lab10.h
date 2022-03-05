#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <chrono>
#include <thread>
#include <mutex>
#include <functional>

using namespace std;

#define MAX_STEP 5
#define MIN_STEP -5

namespace lab10 
{
	struct Vector2d 
	{
		double x, y;
		Vector2d(double x = 0, double y = 0): x(x), y(y) { }
	};

	class Ball 
	{
		Vector2d position;
		const string name;
		const uint16_t id;
		bool is_active;

		static uint16_t current_id;
		
	public:
		Ball(Vector2d position, string name): 
			position(position), name(name), id(current_id++), is_active(true)
		{ }

		Vector2d get_position(void) const noexcept { return this->position; }
		string get_name(void) const noexcept { return this->name; }
		uint16_t get_id(void) const  noexcept { return this->id; }

		void set_active(void) noexcept { this->is_active = !is_active; }
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

		void calculate_motion(Ball* ball, mutex& mute);
	public:
		Renderer(void) = delete;
		Renderer(vector<Ball*> balls, double border_x) 
			: balls(balls), border_x(border_x)
		{ }

		~Renderer() { for (auto i : balls) delete i; }

		void begin(void);
	};

	void lab(void);
}