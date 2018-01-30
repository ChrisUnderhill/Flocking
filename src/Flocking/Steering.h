#pragma once
#include <SFML/Graphics.hpp>

class Steering
{
public:
	virtual sf::Vector2f calculateForce() = 0;
	virtual sf::Vector2f calculateForce(sf::Vector2f pos) = 0;
	virtual sf::Vector2f calculateForce(sf::Vector2f pos, sf::Vector2f vel) = 0;

};

