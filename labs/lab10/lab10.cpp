#include "lab10.h"

using namespace lab10;
uint16_t Ball::current_id = 0;

void Renderer::calculate_motion(Ball* ball, mutex& mute)
{
	srand(time(NULL));
	while (ball->get_position().y > border_x)
	{
		int x_shift = MIN_STEP + (rand() * (int)(MAX_STEP - MIN_STEP) / RAND_MAX),
			y_shift = MIN_STEP + (rand() * (int)(MAX_STEP - MIN_STEP) / RAND_MAX);
		{
			lock_guard<mutex> guard(mute);
			cout << "id: " << ball->get_id() << "\tname: " << ball->get_name()
				<< "\t\tx: " << ball->get_position().x << "\ty: " << ball->get_position().y
				<< "\tdir_x: " << x_shift << "\tdir_y: " << y_shift << endl;
		}

		ball->move_to(Vector2d(x_shift, y_shift));
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Renderer::begin(void)
{
	vector<thread*> _rendering;
	mutex mute;

	for (const auto& i : this->balls)
	{
		function<void()> func = [&]()->void { calculate_motion(i, mute); };
		_rendering.push_back(new thread(func));
	}

	for (auto& i : _rendering) i->join();
	for (auto& i : _rendering) delete i;
}

void lab10::lab(void) 
{
	const Vector2d begin_point(4, -2);
	const int N = 10;
	const double down_border_x = -10;

	vector<Ball*> balls;
	for (int i = 0; i < N; i++) 
	{
		balls.push_back(new Ball(begin_point, "ball_#" + to_string(i)));
	}

	Renderer(balls, down_border_x).begin();
}