#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

const int defwinwidth = 480, defwinheight = 480, width = 24, height = 24;

int getrand() {
	srand(time(NULL));
	return rand();
}

int rand_int(int min, int max) {
	srand(rand() * time(NULL) * rand() * 0.5);
	int num = rand() % (max - min);
	return num + min;
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

	RectangleShape apple;
	apple.setFillColor(Color::Color(172, 50, 50, 255));
	apple.setPosition(rand_int(0, width) * (defwinwidth / width), rand_int(0, height) * (defwinwidth / height));
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
					apple.setPosition(rand_int(0, width) * (defwinwidth / width), rand_int(0, height) * (defwinwidth / height));

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