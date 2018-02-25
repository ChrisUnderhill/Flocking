#include "SimpleAimAt.h"
#include <iostream>
#include <random>
#include "TriFlocker.h"

SimpleAimAt::SimpleAimAt(std::vector<TriFlocker*> * others)
{
	targetPos = sf::Vector2f(rand() % 900, rand() % 900);

	flockers = others;
}


SimpleAimAt::~SimpleAimAt()
{
}


sf::Vector2f SimpleAimAt::calculateForce(sf::Vector2f pos) {
	sf::Vector2f delta = TriFlocker::wrappedDelta(targetPos, pos, sf::Vector2f(1920,1080) );

	//targetPos += sf::Vector2f(0.0001, 0.0001);

	targetPos = sf::Vector2f(800, 600);


	return normalise(delta) * maxForce;
}

void SimpleAimAt::pickRandomTarget() {
	targetPos = sf::Vector2f(rand() % 1000 + 500, rand() % 500 + 250);
}


sf::Vector2f SimpleAimAt::normalise(sf::Vector2f x) {
	float tot = sqrt(x.x*x.x + x.y*x.y);

	return x / tot;
}

