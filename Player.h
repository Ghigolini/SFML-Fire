#pragma once
#include <SFML/Graphics.hpp>
#include "Fire.h"
using namespace sf;

class Player {
public:
	RectangleShape player, up, down, left, right;
	Fire *fire = new Fire(100, Vector2f(10, 10), Color::Color(255, 0, 0)), *fire_ = new Fire(100, Vector2f(10, 10), Color::Color(255, 255, 0));
	Vector2f v = Vector2f(0, 0);
	Player();
	void movement(Time elapsed);
	void fireCollision(Time elapsed, Fire &fireCollided, RenderWindow &window);
	void draw(RenderWindow &window);
private:
	Time burningLifetime = milliseconds(10000);
	bool isBurning;
	int moveSpeed = 5, jumpSpeed = 20;
	bool whileJump;
	void gravity();
	void updateBounds();
};