#include "Player.h"

Player::Player() {
	player.setPosition(100, 100);
	player.setSize(Vector2f(20, 40));
	player.setFillColor(Color::White);

	up.setPosition(player.getPosition());
	up.setSize(Vector2f(player.getSize().x, 1));
	up.setFillColor(Color::Red);

	down.setPosition(player.getPosition().x, player.getPosition().y + player.getSize().y);
	down.setSize(Vector2f(player.getSize().x, 1));
	down.setFillColor(Color::Red);

	right.setPosition(player.getPosition().x + player.getSize().x, player.getPosition().y);
	right.setSize(Vector2f(1, player.getSize().y));
	right.setFillColor(Color::Red);

	left.setPosition(player.getPosition());
	left.setSize(Vector2f(1, player.getSize().y));
	left.setFillColor(Color::Red);

	fire->setEmitter(Vector2f(10000, 10000));
	fire_->setEmitter(Vector2f(10000, 10000));
}

void Player::movement(Time elapsed) {
	player.move(v);
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		v.x = moveSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		v.x = -moveSpeed;
	}
	else {
		v.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && !whileJump) {
		v.y = -jumpSpeed;
	}
	gravity();
	updateBounds();
	fire->update(elapsed);
	fire_->update(elapsed);
	if (isBurning) {
		burningLifetime -= elapsed;
		fire->setEmitter(Vector2f(player.getPosition().x + player.getSize().x / 2 - 5, player.getPosition().y + player.getSize().y / 1.2));
		fire_->setEmitter(Vector2f(player.getPosition().x + player.getSize().x / 2 - 5, player.getPosition().y + player.getSize().y / 1.2));
	}
	else {
		burningLifetime = milliseconds(10000);
	}
	if (burningLifetime <= Time::Zero) {
		fire->setEmitter(Vector2f(10000, 10000));
		fire_->setEmitter(Vector2f(10000, 10000));
		isBurning = false;
	}
}

void Player::gravity() {
	if (player.getPosition().y + player.getSize().y <= 1000) {
		v.y += 1;
		whileJump = true;
	}
	else {
		player.setPosition(player.getPosition().x, 1000 - player.getSize().y);
		whileJump = false;
	}
}

void Player::updateBounds() {
	up.setPosition(player.getPosition());
	down.setPosition(player.getPosition().x, player.getPosition().y + player.getSize().y);
	right.setPosition(player.getPosition().x + player.getSize().x, player.getPosition().y);
	left.setPosition(player.getPosition());
}

void Player::draw(RenderWindow &window) {
	window.draw(player);
	window.draw(up);
	window.draw(down);
	window.draw(left);
	window.draw(right);
	fire->draw(window);
	fire_->draw(window);
}

void Player::fireCollision(Time elapsed, Fire &fireCollided, RenderWindow &window) {
	if (fireCollided.isColliding(player)) {
		fire->setEmitter(Vector2f(player.getPosition().x + player.getSize().x / 2 - 5, player.getPosition().y + player.getSize().y / 1.2));
		fire_->setEmitter(Vector2f(player.getPosition().x + player.getSize().x / 2 - 5, player.getPosition().y + player.getSize().y / 1.2));
		isBurning = true;
	}
}