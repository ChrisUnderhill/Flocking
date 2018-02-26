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
	float tot = sqrt(x.x*x.x + x.y*x.y);

	if (tot > 0.001 || tot < -0.001) {
		return x / tot;
	}
	
	return sf::Vector2f(0, 0);
}

float SeeingBoids::size2(sf::Vector2f x) {
	return sqrt(x.x*x.x + x.y*x.y);
}
