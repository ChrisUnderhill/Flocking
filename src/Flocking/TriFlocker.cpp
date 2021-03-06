#include "TriFlocker.h"
#include "Steering.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#define pi 3.14159265;

TriFlocker::TriFlocker(sf::RenderWindow* win)
{
	size = 20;
	triShape.setPointCount(3);
	triShape.setPoint(0, sf::Vector2f(0, 0));
	triShape.setPoint(1, sf::Vector2f(20, 0));
	triShape.setPoint(2, sf::Vector2f(20 / 2, 20 * 2));
	triShape.setOrigin(20 / 2, 20);

	color = sf::Color(255, 0, 0);
	triShape.setFillColor(color);

	outColor = sf::Color(127, 0, 0);
	triShape.setOutlineColor(outColor);

	outThickness = 20 / 10;
	triShape.setOutlineThickness(outThickness);

	angle = 0;
	pos = sf::Vector2f(0, 0);
	vel = sf::Vector2f(0, 0);
	acc = sf::Vector2f(0, 0);

	window = win;

	drag = 1;

}

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
	vel = sf::Vector2f(0, 0);
	acc = sf::Vector2f(0, 0);

	window = win;

	drag = 0.995;

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

sf::Vector2f TriFlocker::getPos() { return pos; }

sf::Vector2f TriFlocker::getVel() { return vel; }

sf::Vector2f TriFlocker::wrappedDelta(sf::Vector2f u, sf::Vector2f v, sf::Vector2f WrapBoxSize) {

	sf::Vector2f delta = u-v;

	if (delta.x > WrapBoxSize.x / 2) { delta.x = delta.x - WrapBoxSize.x; }
	else if (delta.x < -WrapBoxSize.x / 2) { delta.x = WrapBoxSize.x + delta.x; }


	if (delta.y > WrapBoxSize.y / 2) { delta.y = delta.y - WrapBoxSize.y; }
	else if (delta.y < -WrapBoxSize.y / 2) { delta.y = WrapBoxSize.y + delta.y; }
	
	return delta;
}

void TriFlocker::setSteering(Steering* s) {
	steering = s;
}

void TriFlocker::initRandom() {
	pos = sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y);
	angle = rand() % 360;
}

void TriFlocker::update() {
	acc = steering->calculateForce(pos);
	vel += acc;
	pos += vel;

	angle = atan2(-vel.x, vel.y) * 180/pi;
	triShape.setRotation(angle);


	sf::Vector2f renderPos = sf::Vector2f( fmod(pos.x, window->getSize().x), fmod(pos.y, window->getSize().y));
	renderPos.x = renderPos.x < 0 ? window->getSize().x + renderPos.x : renderPos.x;
	renderPos.y = renderPos.y < 0 ? window->getSize().y + renderPos.y : renderPos.y;

	pos = renderPos;
	triShape.setPosition(renderPos);

	vel = sf::Vector2f(vel.x * drag, vel.y*drag);

}

void TriFlocker::draw() {
	try {
		window->draw(triShape);
	}
	catch (const std::exception& e) {
		std::cout << "That window no longer exists\n" << e.what() << std::endl;
	}
}
