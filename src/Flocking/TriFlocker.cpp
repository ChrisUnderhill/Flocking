#include "TriFlocker.h"
#include <SFML/Graphics.hpp>


TriFlocker::TriFlocker(int base, sf::Vector2f loc, sf::RenderWindow* win)
{
	size = base;
	triShape.setPointCount(3);
	triShape.setPoint(0, sf::Vector2f(0, 0));
	triShape.setPoint(1, sf::Vector2f(base, 0));
	triShape.setPoint(2, sf::Vector2f(base/2, base*2));
	triShape.setOrigin(base / 2, base);

	color = sf::Color(255, 0, 0);
	triShape.setFillColor(color);

	outColor = sf::Color(127, 0, 0);
	triShape.setOutlineColor(outColor);

	outThickness = base / 10;
	triShape.setOutlineThickness(outThickness);

	angle = 0;
	pos = loc;

	window = win;

}


TriFlocker::~TriFlocker()
{
}


void TriFlocker::setColor(sf::Color col) {
	color = col;
	triShape.setFillColor(col);
}

void TriFlocker::setOutColor(sf::Color col) {
	outColor = col;
	triShape.setOutlineColor(col);
}

void TriFlocker::setThickness(int thick) {
	outThickness = thick;
	triShape.setOutlineThickness(thick);
}

void TriFlocker::setSize(int s) {
	size = s;
}

void TriFlocker::move(sf::Vector2f delta) {
	pos += delta;
}

void TriFlocker::move(float deltax, float deltay) {
	pos += sf::Vector2f(deltax, deltay);
}

void TriFlocker::rotate(float theta) {
	angle += theta;
}

void TriFlocker::update() {
	triShape.setPosition(pos);
	triShape.setRotation(angle); 
}

void TriFlocker::draw() {
	window->draw(triShape);
}
