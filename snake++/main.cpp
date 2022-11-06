#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;


const int defwinwidth = 480, defwinheight = 480, width = 24, height = 24, tps = 16, max_length = ((width - 1) * (height - 1));
long lastTickTime = 0;

enum SnakeDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

int apple_x = 0, apple_y = 0;
RectangleShape apple;

int snake_head_x = 0, snake_head_y = 0, snake_length = 3, spawn_boundries = 4;
SnakeDirection snake_dir = UP, last_snake_dir = UP;
RectangleShape snakehead;

int prev_snake_x[max_length], prev_snake_y[max_length];
RectangleShape bodyrender;

int score = 0;

RenderWindow window(VideoMode(defwinwidth, defwinheight), "Snake++ by DillyzThe1 v1.1");

int getrand() {
	srand(rand() * time(NULL) * rand() * 0.5);
	return rand();
}

int rand_int(int min, int max) {
	int num = getrand() % (max - min);
	return num + min;
}

bool wall_at(int xx, int yy) {
	if (xx == -1)
		return true;
	if (xx == width)
		return true;

	if (yy == -1)
		return true;
	if (yy == height)
		return true;

	return false;
}

bool snake_head_at(int xx, int yy) {
	if (snake_head_x == xx && snake_head_y == yy)
		return true;
	return false;
}

bool snake_body_at(int xx, int yy) {
	for (int i = 0; i < (snake_length - 1); i++)
		if (prev_snake_x[i] == xx && prev_snake_y[i] == yy)
			return true;
	return false;
}

bool snake_at(int xx, int yy) {
	return snake_head_at(xx, yy) || snake_body_at(xx, yy);
}

void apple_respawn() {
	apple_x = rand_int(0, width);
	apple_y = rand_int(0, height);

	if (snake_at(apple_x, apple_y))
	{
		apple_respawn();
		return;
	}

	apple.setPosition(apple_x * (defwinwidth / width), apple_y * (defwinwidth / height));
}

void snake_respawn() {
	score = 0;
	snake_dir = UP;
	snake_length = 3;
	last_snake_dir = UP;
	apple_respawn();

	snake_head_x = rand_int(spawn_boundries, width - spawn_boundries);
	snake_head_y = height - spawn_boundries;

	for (int i = 0; i < max_length; i++) {
		prev_snake_x[i] = snake_head_x;
		prev_snake_y[i] = snake_head_y + i + 1;
	}
}

void insert_prev(int xx, int yy) {
	int lastx = prev_snake_x[0];
	int lasty = prev_snake_y[0];

	for (int i = 1; i < max_length - 1; i++) {
		int almostlastx = prev_snake_x[i];
		int almostlasty = prev_snake_y[i];

		prev_snake_x[i] = lastx;
		prev_snake_y[i] = lasty;

		lastx = almostlastx;
		lasty = almostlasty;
	}

	prev_snake_x[0] = xx;
	prev_snake_y[0] = yy;
}

void tick() {
	//cout << "Tick!\n";

	insert_prev(snake_head_x, snake_head_y);

	switch (snake_dir) {
		case SnakeDirection::UP:
			snake_head_y--;
			break;
		case SnakeDirection::DOWN:
			snake_head_y++;
			break;
		case SnakeDirection::LEFT:
			snake_head_x--;
			break;
		case SnakeDirection::RIGHT:
			snake_head_x++;
			break;
		default:
			cout << "Invalid Snake Tick! ";
			cout << snake_dir;
			cout << "\n";
			break;
	}

	last_snake_dir = snake_dir;

	if (snake_head_at(apple_x, apple_y)) {
		score += 100;
		snake_length++;

		cout << "New snake length: ";
		cout << snake_length;
		cout << "\n";

		apple_respawn();
	}

	if (snake_body_at(snake_head_x, snake_head_y) || wall_at(snake_head_x, snake_head_y) || snake_length >= max_length)
		snake_respawn();
}

int main() {
	srand(time(0));
	cout << "C++ is cool.\n";

	window.setFramerateLimit(120);

	Texture icon;
	if (icon.loadFromFile("images/logo.png")) {
		Image iconImg;
		iconImg = icon.copyToImage();
		window.setIcon(350, 350, iconImg.getPixelsPtr());
	}
	else
		cout << "Icon loading FAIL!";

	apple.setFillColor(Color::Color(172, 50, 50, 255));
	apple.setSize(Vector2f::Vector2(defwinwidth / width, defwinwidth / height));

	snakehead.setFillColor(Color::Color(152, 229, 80, 255));
	snakehead.setSize(Vector2f::Vector2(defwinwidth / width, defwinwidth / height));

	bodyrender.setFillColor(Color::Color(106, 190, 48, 255));
	bodyrender.setSize(Vector2f::Vector2(defwinwidth / width, defwinwidth / height));

	snake_respawn();

	while (window.isOpen()) {

		long cpuTime = clock();
		if (cpuTime - lastTickTime >= 1000 / tps)
		{
			lastTickTime = cpuTime;
			tick();
		}

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				switch(e.key.code) {
					case Keyboard::Escape:
						window.close();
						break;
					case Keyboard::Enter:
						snake_respawn();
						break;
					case Keyboard::Up:
						if (last_snake_dir != SnakeDirection::DOWN)
							snake_dir = SnakeDirection::UP;
						break;
					case Keyboard::Down:
						if (last_snake_dir != SnakeDirection::UP)
							snake_dir = SnakeDirection::DOWN;
						break;
					case Keyboard::Left:
						if (last_snake_dir != SnakeDirection::RIGHT)
							snake_dir = SnakeDirection::LEFT;
						break;
					case Keyboard::Right:
						if (last_snake_dir != SnakeDirection::LEFT)
							snake_dir = SnakeDirection::RIGHT;
						break;
				}

			if (e.type == Event::Resized)
			{
				int avgAmount = (window.getSize().x + window.getSize().y) / 2;
				window.setSize(Vector2u::Vector2(avgAmount, avgAmount));
			}
		}

		snakehead.setPosition(snake_head_x * (defwinwidth / width), snake_head_y * (defwinwidth / height));

		window.clear(Color::Color(34, 32, 52, 255));

		for (int i = 0; i < (snake_length - 1); i++) {
			bodyrender.setPosition(prev_snake_x[i] * (defwinwidth / width), prev_snake_y[i] * (defwinwidth / width));
			window.draw(bodyrender);
		}

		window.draw(apple);
		window.draw(snakehead);
		window.display();
	}

	return 0;
}