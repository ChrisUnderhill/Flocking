#pragma once
#include <SFML/Graphics.hpp>

class Steering
{
public:
	virtual sf::Vector2f calculateForce() { return sf::Vector2f(0, 0); }
	virtual sf::Vector2f calculateForce(sf::Vector2f pos) { return sf::Vector2f(0, 0); }
	virtual sf::Vector2f calculateForce(sf::Vector2f pos, sf::Vector2f vel) { return sf::Vector2f(0, 0); }

};

