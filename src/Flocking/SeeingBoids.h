#pragma once
#include "Steering.h"
#include "TriFlocker.h"
#include <SFML/Graphics.hpp>

class SeeingBoids :
	public Steering
{
public:
	SeeingBoids(std::vector<TriFlocker*> * others);
	~SeeingBoids();

	sf::Vector2f calculateForce(sf::Vector2f pos);

	float visionRadius;

	sf::Vector2f worldSize;


protected:
	sf::Vector2f targetPos = sf::Vector2f(200,500);
	sf::Vector2f normalise(sf::Vector2f x);
	float size2(sf::Vector2f x);

	float maxForce = 0.01;


};

