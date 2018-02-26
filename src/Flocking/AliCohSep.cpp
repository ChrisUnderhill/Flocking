#include "AliCohSep.h"
#include <iostream>
#include <cassert>



AliCohSep::AliCohSep(std::vector<TriFlocker*> * others) : SeeingBoids(others){
	alignment = 0.0/8;
	cohesion = 0.0/8;
	separation = 80.0/8;

	maxForce = 0.02;
	visionRadius = 30;
}


AliCohSep::~AliCohSep()
{
}

sf::Vector2f AliCohSep::calculateForce(sf::Vector2f pos) {

	targetAli = sf::Vector2f(0, 0);
	targetCoh = sf::Vector2f(0, 0);
	targetSep = sf::Vector2f(0, 0);
	int count = 0;
	
	for (TriFlocker* tri : *flockers) {
		sf::Vector2f delta = TriFlocker::wrappedDelta(tri->getPos(), pos, worldSize);

		assert( (delta.x < 980 && delta.y < 570) );

		if (size2(delta) < visionRadius*visionRadius && size2(delta) > 0) {

			targetAli += calcAlignment(tri);
			targetCoh += calcCohesion(delta);
			targetSep += calcSeparation(delta);

			count++;
		}
	}

	if (count > 0) {
		sf::Vector2f deltaAli = normalise(targetAli) * alignment;
		//sf::Vector2f deltaCoh = sf::Vector2f( ( targetCoh.x / count - pos.x ) * cohesion, (targetCoh.y / count ) * cohesion);
		sf::Vector2f deltaCoh = normalise(targetCoh /* * (1.0f / count) - pos */ )*cohesion;


		sf::Vector2f deltaSep = normalise(targetSep) * separation;

		//std::cout << deltaCoh.x << " " << deltaCoh.y << std::endl;

		return (deltaAli + deltaCoh + deltaSep) * maxForce;
	}
	return sf::Vector2f(0, 0);
}


inline sf::Vector2f AliCohSep::calcAlignment(TriFlocker* tri) {
	return tri->getVel();
}

inline sf::Vector2f AliCohSep::calcCohesion(sf::Vector2f delta) {
	return delta *(1.0f);
}

inline sf::Vector2f AliCohSep::calcSeparation(sf::Vector2f delta) {
	return normalise(-delta) / size2(delta);
}