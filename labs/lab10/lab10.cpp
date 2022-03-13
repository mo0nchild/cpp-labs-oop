#include "lab10.h"

using namespace lab10;
uint16_t Ball::current_id = 0;

void Renderer::calculate_motion(Ball* ball, mutex& mute, vector<int> rand_values)
{
	int16_t shift_rand = 0;
	
	mute.lock();
	Vector2d pos = ball->get_position();
	mute.unlock();

	while ((fabs(pos.y) < this->render_size.second - 1 && pos.y > this->border_x)
		&& fabs(pos.x) < this->render_size.first - 1)
	{
		{
			lock_guard<mutex> guard(mute);
			if (shift_rand >= rand_values.size() - 1) shift_rand = 0;
			else shift_rand++;

			int x_shift = rand_values[shift_rand], y_shift = rand_values[rand_values.size() - 1 - shift_rand];;
		
			/*for (int i : rand_values) cout << i << "\t";
			cout << endl;*/

			/*cout << "id: " << ball->get_id() << "\tname: " << ball->get_name()
				<< "\t\tx: " << ball->get_position().x << "\ty: " << ball->get_position().y
				<< "\tdir_x: " << x_shift << "\tdir_y: " << y_shift << endl;*/

			ball->move_to(Vector2d(x_shift, y_shift));
			pos = ball->get_position();
		}
		this_thread::sleep_for(chrono::milliseconds(400));
	} 
	ball->set_active(!ball->get_active());
}

void Renderer::begin(vector<CoolPriority> priority)
{
	if (this->balls.size() != priority.size()) throw exception("Разная длина массивов приоритета и объектов");

	vector<thread*> _rendering;
	vector<vector<int>> rand_list;
	
	mutex mute;
	int16_t balls_size = balls.size();

	for (int16_t i = 0; i < balls.size(); i++) 
	{
		rand_list.push_back(vector<int>());
		for (int k = 0; k < RANDOM_SIZE; k++)
		{
			int16_t value = ((double)rand() / RAND_MAX) * (MAX_STEP - MIN_STEP) + MIN_STEP;
			rand_list[i].push_back(value);
		}
	}

	for (int16_t i = 0; i < balls.size(); i++)
	{
		vector<int> list = rand_list[i];
		function<void(int)> func = [&](int x)->void { calculate_motion(this->balls[x], mute, list); };
		_rendering.push_back(new thread(func, i));

		this_thread::sleep_for(chrono::milliseconds(100));

		SetThreadPriority(_rendering[i]->native_handle(), (int16_t)priority[i]);
	}

	auto check_location = [&](int x, int y) -> bool
	{
		bool result = false;

		mute.lock();
		for (auto o: this->balls)
		{
			Vector2d pos = o->get_position();
			if ((int16_t)pos.x == x && (int16_t)pos.y == y && o->get_active()) 
				result = true;
		}
		mute.unlock();

		return result;
	};

	stringstream str_buffer;
	for (int16_t x = 0; x <= this->render_size.first; x++) str_buffer << "--";

	while (true)
	{
		int16_t destroyed_balls = 0;
		
		mute.lock();
		for (auto o : this->balls) 
		{
			if (!(o->get_active())) destroyed_balls++;
		}
		mute.unlock();
		if (destroyed_balls == balls_size) break;

		system("cls");
		cout << "Осталось в живых: " << balls_size - destroyed_balls << endl;

		cout << str_buffer.str() << endl;
		for (int16_t y = this->render_size.second / 2; y >= -(this->render_size.second / 2); y--)
		{
			if(y + 1 == this->border_x) cout << str_buffer.str() << endl;
			for (int16_t x = -(this->render_size.first / 2); x <= this->render_size.first / 2; x++)
			{
				if (check_location(x, y)) cout << "o ";
				else cout << "  ";
			}
			cout << endl;
		}
		cout << str_buffer.str() << endl;

		this_thread::sleep_for(chrono::milliseconds(400));
	}

	for (auto& i: _rendering) i->join();

}

void lab10::lab(void) 
{
	srand(time(0));

	const Vector2d begin_point(0, 0);
	const double down_border_x = -8;
	const int N = 20, RANGE = 10;
	
	vector<CoolPriority> priotiries;
	vector<Ball*> balls;
	
	for (int i = 0; i < N; i++) 
	{
		balls.push_back(new Ball(Vector2d(-(RANGE / 2) + i * 2, 3), "ball_#" + to_string(i)));
		priotiries.push_back(CoolPriority::ABOVE_NORMAL);
	}

	Renderer(balls, down_border_x, pair<int, int>(40, 30)).begin(priotiries);
}