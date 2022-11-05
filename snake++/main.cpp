#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

const int defwinwidth = 480, defwinheight = 480, width = 24, height = 24;

int apple_x = 0, apple_y = 0;
RectangleShape apple;

int getrand() {
	srand(time(NULL));
	return rand();
}

int rand_int(int min, int max) {
	srand(rand() * time(NULL) * rand() * 0.5);
	int num = rand() % (max - min);
	return num + min;
}

bool snake_at(int x, int y) {
	return false;
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

int main() {
	srand(time(0));
	cout << "C++ is cool.";

	RenderWindow window(VideoMode(defwinwidth, defwinheight), "Snake++ by DillyzThe1");
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
	apple_respawn();
	apple.setSize(Vector2f::Vector2(defwinwidth / width, defwinwidth / height));

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
					window.close();
				else if (e.key.code == Keyboard::Enter)
					apple_respawn();

			if (e.type == Event::Resized)
			{
				int avgAmount = (window.getSize().x + window.getSize().y) / 2;
				window.setSize(Vector2u::Vector2(avgAmount, avgAmount));
			}
		}

		window.clear(Color::Color(34, 32, 52, 255));
		window.draw(apple);
		window.display();
	}

	return 0;
}