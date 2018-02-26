#include "SeeingBoids.h"
#include <iostream>
#include <random>
#include "TriFlocker.h"

SeeingBoids::SeeingBoids(std::vector<TriFlocker*> * others)
{
	targetPos = sf::Vector2f(0,0);

	flockers = others;

	worldSize = sf::Vector2f(1920, 1080);

	visionRadius = 10;
}


SeeingBoids::~SeeingBoids()
{
}


sf::Vector2f SeeingBoids::calculateForce(sf::Vector2f pos) {

	targetPos = sf::Vector2f(0, 0);
	int count = 0;
	/**/
	for (TriFlocker* tri : *flockers) {
		sf::Vector2f delta = TriFlocker::wrappedDelta(tri->getPos(), pos, worldSize);

		if (size2(delta) < visionRadius*visionRadius && size2(delta) > 0 ) {
			//std::cout << "I SEE SOMEONE";

			targetPos += tri->getPos();
			count++;
		}
	}
	//std::cout << "I see " << targetPos.x << " other flockers" << std::endl;

	if (count > 0) {
		sf::Vector2f delta = sf::Vector2f(targetPos.x / count, targetPos.y / count) - pos;

		return normalise(delta) * maxForce;
	}
	return sf::Vector2f(1e-5, 0);
}

sf::Vector2f SeeingBoids::normalise(sf::Vector2f x) {
	float sqr = x.x*x.x + x.y*x.y;

	float f;
	long i;

	float x2;
	const float threehalfs = 1.5F;

	x2 = sqr * 0.5f;
	f = sqr;
	i = *(long *)&f;

	i = 0x5f3759df - (i >> 1);

	f = *(float *)&i;
	f = f * (threehalfs - (x2*f*f));


	

	if (f > 0.0001 || f < -0.0001) {
		return x * f;
	}
	
	return sf::Vector2f(0, 0);
}

float SeeingBoids::size2(sf::Vector2f x) {
	return x.x*x.x + x.y*x.y;
}
