#include "SimpleAimAt.h"
#include <iostream>
#include <random>


SimpleAimAt::SimpleAimAt()
{
	targetPos = sf::Vector2f(rand() % 900, rand() % 900);
}


SimpleAimAt::~SimpleAimAt()
{
}

sf::Vector2f SimpleAimAt::calculateForce() {
	return sf::Vector2f(0, 0);
}


sf::Vector2f SimpleAimAt::calculateForce(sf::Vector2f pos) {
	sf::Vector2f delta = targetPos - pos;

	targetPos += sf::Vector2f(0.0001, 0.0001);

	return normalise(delta) * maxForce;
}

sf::Vector2f SimpleAimAt::calculateForce(sf::Vector2f pos, sf::Vector2f vel) {
	return sf::Vector2f(0, 0);
}

void SimpleAimAt::pickRandomTarget() {
	targetPos = sf::Vector2f(rand() % 1000 + 500, rand() % 500 + 250);
}


sf::Vector2f SimpleAimAt::normalise(sf::Vector2f x) {
	float tot = sqrt(x.x*x.x + x.y*x.y);

	return x / tot;
}
