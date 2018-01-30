#pragma once
#include "Steering.h"
#include <SFML/Graphics.hpp>

class SimpleAimAt :
	public Steering
{
public:
	SimpleAimAt();
	~SimpleAimAt();

	sf::Vector2f calculateForce();
	sf::Vector2f calculateForce(sf::Vector2f pos);
	sf::Vector2f calculateForce(sf::Vector2f pos, sf::Vector2f vel);

	void pickRandomTarget();

private:
	sf::Vector2f targetPos = sf::Vector2f(200,500);
	sf::Vector2f normalise(sf::Vector2f x);

	float maxForce = 0.01;


};

