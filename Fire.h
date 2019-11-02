#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Fire {
public:
	Fire(int count, Vector2f size, Color color);
	Color color;
	void setEmitter(Vector2f position);
	void update(Time elapsed);
	bool isColliding(RectangleShape rect);
	void draw(RenderWindow &window);
private:
	struct Particle {
		Vector2f v, size, pos;
		Time lifetime;
	};
	void resetParticle(int i);
	vector<Particle> particles;
	vector<RectangleShape> vertices;
	Vector2f emitter;
	Time lifetime;
};