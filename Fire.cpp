#include "Fire.h"

Fire::Fire(int count, Vector2f size, Color color) : particles(count), vertices(count), lifetime(seconds(3)){
	for (int i = 0; i < particles.size(); i++) {
		vertices[i].setSize(size);
		this->color = color;
	}
}

void Fire::setEmitter(Vector2f position) {
	emitter = position;
}

void Fire::update(Time elapsed) {
	for (int i = 0; i < particles.size(); i++) {
		Particle &p = particles[i];
		p.lifetime -= elapsed;
		if (p.lifetime <= Time::Zero) {
			resetParticle(i);
		}
		vertices[i].setPosition(vertices[i].getPosition() + p.v * elapsed.asSeconds());

		float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
		vertices[i].setFillColor(Color::Color(color.r, color.g, color.b, ratio * 255));

		vertices[i].rotate((rand() % 200 - 100) * elapsed.asSeconds());
	}
}

void Fire::draw(RenderWindow &window) {
	for (int i = 0; i < vertices.size(); i++) {
		window.draw(vertices[i]);
	}
}

void Fire::resetParticle(int i) {
	float angle = (rand() % 360) * 3.14 / 180;
	float speed = rand() % 100 - 50;
	particles[i].v = Vector2f(speed * cos(angle), -100 + speed * sin(angle));
	particles[i].lifetime = milliseconds((rand() % 2000) + 1000);

	vertices[i].setPosition(emitter);
}

bool Fire::isColliding(RectangleShape rect) {
	for (int i = 0; i < particles.size(); i++) {
		return rect.getGlobalBounds().intersects(vertices[i].getGlobalBounds());
	}
}