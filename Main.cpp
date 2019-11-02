#include <SFML/Graphics.hpp>
#include <iostream>
#include "Fire.h"
#include "Player.h"
using namespace sf;
using namespace std;

int main() {
	Fire fire(100, Vector2f(10, 10), Color::Color(255, 0, 0));
	Fire fire_(100, Vector2f(10, 10), Color::Color(255, 255, 0));
	Player player;
	RenderWindow window(VideoMode(1920, 1080), "SFML", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	Clock clock;

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		Vector2i mousePos = Mouse::getPosition(window);
		fire.setEmitter(window.mapPixelToCoords(mousePos));
		fire_.setEmitter(window.mapPixelToCoords(mousePos));

		Time elapsed = clock.restart();
		fire.update(elapsed);
		fire_.update(elapsed);

		player.movement(elapsed);
		player.fireCollision(elapsed, fire, window);
		player.fireCollision(elapsed, fire_, window);

		window.clear();
		player.draw(window);
		fire.draw(window);
		fire_.draw(window);
		window.display();
	}

}