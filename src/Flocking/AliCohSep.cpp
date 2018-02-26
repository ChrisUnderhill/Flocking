#include "AliCohSep.h"
#include <iostream>
#include <cassert>



AliCohSep::AliCohSep(std::vector<TriFlocker*> * others) : SeeingBoids(others){
	alignment = 1.0/8;
	cohesion = 5.0/8;
	separation = 8.0/8;

	maxForce = 0.02;
	visionRadius = 100;
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


		sf::Vector2f deltaSep = targetSep * separation;

		//std::cout << deltaCoh.x << " " << deltaCoh.y << std::endl;

		return (deltaAli + deltaCoh + deltaSep) * maxForce;
	}
	return sf::Vector2f(0, 0);
}

void AliCohSep::setParameters(float ali, float coh, float sep, float vis, float force) {
	alignment = ali;
	cohesion = coh;
	separation = sep;
	visionRadius = vis;
	maxForce = force;
}

void AliCohSep::changeParameter(ReynoldParameters param, float delta) {
	switch (param)
	{
	case ReynoldParameters::alignment:
		alignment += delta;
		break;
	case ReynoldParameters::cohesion:
		cohesion += delta;
		break;
	case ReynoldParameters::separation:
		separation += delta;
		break;
	case ReynoldParameters::visionRadius:
		visionRadius += delta;
		break;
	case ReynoldParameters::maxForce:
		maxForce += delta;
		break;
	default:
		std::cout << "That is not a parameter\n";
		return;
	}
}


inline sf::Vector2f AliCohSep::calcAlignment(TriFlocker* tri) {
	return tri->getVel();
}

inline sf::Vector2f AliCohSep::calcCohesion(sf::Vector2f delta) {
	return delta *(1.0f);
}

inline sf::Vector2f AliCohSep::calcSeparation(sf::Vector2f delta) {
	return -delta / size2(delta) * visionRadius * 0.05f;
}