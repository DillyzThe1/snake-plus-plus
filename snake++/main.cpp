#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

int main() {
	srand(time(0));
	cout << "C++ is cool.";

	RenderWindow window(VideoMode(480, 480), "Snake++ by DillyzThe1");
	window.setFramerateLimit(120);

	Texture icon;
	if (icon.loadFromFile("images/logo.png")) {
		Image iconImg;
		iconImg = icon.copyToImage();
		window.setIcon(350, 350, iconImg.getPixelsPtr());
	}
	else
		cout << "Icon loading FAIL!";

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
					window.close();
		}

		window.clear(Color::Color(175, 175, 175, 255));
		window.display();
	}

	return 0;
}