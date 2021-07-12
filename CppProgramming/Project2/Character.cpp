#include "Character.h"

using namespace Graph_lib;

const int grid_width = 8;
const int grid_height = 8;

Character::Character(Graph_lib::Window* win, int r, int c)
	: my_window{ win }, pos_row { r }, pos_col{ c }, my_enemy{ nullptr }
{
}

void Character::move()
{
	pair<int, int> dir = nextDirection();

	int dr = dir.first;
	int dc = dir.second;
	pos_row += dr;
	pos_col += dc;

	int w = my_window->x_max() / grid_width;
	int h = my_window->y_max() / grid_height;
	for (Shape* s : body_shapes)
	{
		s->move(w*dc, h*dr);
	}
}

pair<int, int> Character::nextDirection()
{
	return make_pair(0, 0);
}

Dummy::Dummy(Graph_lib::Window * win, int r, int c)
	: Character(win, r, c)
{
	int w = win->x_max() / grid_width;
	int h = win->y_max() / grid_height;

	Graph_lib::Ellipse* body = new Graph_lib::Ellipse(Point(c*w + w / 2, r*h + h / 2), w / 2, h / 2);
	body->set_color(Color::black);
	body_shapes.push_back(body);

	win->attach(*body);
}

pair<int, int> Dummy::nextDirection()
{
	vector<pair<int, int>> directions = { { -1,0 },{ +1,0 },{ 0,-1 },{ 0,+1 } };
	random_shuffle(directions.begin(), directions.end());

	int dr = 0, dc = 0, new_r = 0, new_c = 0;
	for (int i = 0; i < 4; i++)
	{
		dr = directions[i].first;
		dc = directions[i].second;
		new_r = pos_row + dr;
		new_c = pos_col + dc;

		if (new_r >= 0 && new_r < grid_height &&
			new_c >= 0 && new_c < grid_width)
			return directions[i];
	}
}

Pursuer::Pursuer(Graph_lib::Window* win, int r, int c)
	: Character(win, r, c)
{
	int w = win->x_max() / grid_width;
	int h = win->y_max() / grid_height;
	int center_x = c * w + w / 2;
	int center_y = r * h + h / 2;

	Graph_lib::Star* body = new Graph_lib::Star(Point(center_x, center_y), 20, 24, 40);
	body->set_color(Color::black);
	body->set_fill_color(Color::dark_red);
	body_shapes.push_back(body);
	win->attach(*body);

	Graph_lib::Star* body2 = new Graph_lib::Star(Point(center_x, center_y), 4, 4, 8);
	body2->set_color(Color::black);
	body2->set_fill_color(Color::red);
	body_shapes.push_back(body2);
	win->attach(*body2);

	for (int i = -20; i <= 20; i += 40)
		for (int j = -20; j <= 20; j += 40) {
			Graph_lib::Star* body3 = new Graph_lib::Star(Point(center_x + i, center_y + j), 8, 6, 10);
			body3->set_color(Color::black);
			body3->set_fill_color(Color::red);
			body_shapes.push_back(body3);
			win->attach(*body3);
		}
}
pair<int, int> Pursuer::nextDirection()
{
	vector<pair<int, int>> directions;
	if (pos_row <= enemy()->row())
		directions.push_back({ +1, 0 });
	if (pos_row >= enemy()->row())
		directions.push_back({ -1, 0 });
	if (pos_col <= enemy()->col())
		directions.push_back({ 0, +1 });
	if (pos_col >= enemy()->col())
		directions.push_back({ 0, -1 });

	random_shuffle(directions.begin(), directions.end());

	int dr = 0, dc = 0, new_r = 0, new_c = 0;
	for (pair<int, int> dir : directions)
	{
		dr = dir.first;
		dc = dir.second;
		new_r = pos_row + dr;
		new_c = pos_col + dc;

		if (new_r >= 0 && new_r < grid_height &&
			new_c >= 0 && new_c < grid_width)
			return dir;
	}
}

Evader::Evader(Graph_lib::Window* win, int r, int c)
	: Character(win, r, c)
{
	int w = win->x_max() / grid_width;
	int h = win->y_max() / grid_height;
	int center_x = c * w + w / 2;
	int center_y = r * h + h / 2;

	for (int i = -30; i <= 60; i += 60)
		for (int j = -30; j <= 60; j += 60) {
			Graph_lib::Circle* body2 = new Graph_lib::Circle(Point(center_x + i, center_y + j), 10);
			body2->set_color(Color::black);
			body2->set_fill_color(Color::blue);
			body_shapes.push_back(body2);
			win->attach(*body2);
		}

	Graph_lib::Circle* body = new Graph_lib::Circle(Point(center_x, center_y), 40);
	body->set_color(Color::black);
	body->set_fill_color(Color::dark_blue);
	body_shapes.push_back(body);
	win->attach(*body);

	Graph_lib::Circle* body2 = new Graph_lib::Circle(Point(center_x, center_y), 8);
	body2->set_color(Color::black);
	body2->set_fill_color(Color::blue);
	body_shapes.push_back(body2);
	win->attach(*body2);
}
pair<int, int> Evader::nextDirection()
{
	vector<pair<int, int>> directions;
	bool up = pos_row <= enemy()->row();
	bool down = pos_row >= enemy()->row();
	bool left = pos_col <= enemy()->col();
	bool right = pos_col >= enemy()->col();

	if (up) directions.push_back({ -1, 0 });
	if (down) directions.push_back({ +1, 0 });
	if (left) directions.push_back({ 0, -1 });
	if (right) directions.push_back({ 0, +1 });

	random_shuffle(directions.begin(), directions.end());

	int dr = 0, dc = 0, new_r = 0, new_c = 0;
	for (pair<int, int> dir : directions)
	{
		dr = dir.first;
		dc = dir.second;
		new_r = pos_row + dr;
		new_c = pos_col + dc;

		if (new_r >= 0 && new_r < grid_height &&
			new_c >= 0 && new_c < grid_width)
			return dir;
	}
	if (rand() % 2 == 0)
		return { up ? +1 : down ? -1 : 0, 0 };
	else
		return { 0, left ? +1 : right ? -1 : 0 };
}