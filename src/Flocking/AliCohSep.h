#pragma once
#include "SeeingBoids.h"
class AliCohSep :
	public SeeingBoids
{
public:
	AliCohSep(std::vector<TriFlocker*> * others);
	~AliCohSep();

	sf::Vector2f calculateForce(sf::Vector2f pos);

private:
	float alignment, cohesion, separation;

	float targetSpeed;

	sf::Vector2f targetAli = sf::Vector2f(0, 0);
	sf::Vector2f targetCoh = sf::Vector2f(0, 0);
	sf::Vector2f targetSep = sf::Vector2f(0, 0);


	sf::Vector2f calcAlignment(TriFlocker* tri);
	sf::Vector2f calcCohesion(sf::Vector2f delta);
	sf::Vector2f calcSeparation(sf::Vector2f delta);
};

