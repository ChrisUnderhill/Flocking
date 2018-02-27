#include "AliCohSep.h"
#include <iostream>
#include <cassert>



AliCohSep::AliCohSep(std::vector<TriFlocker*> * others) : SeeingBoids(others){
	alignment = 1.0/8;
	cohesion = 5.0/8;
	separation = 8.0/8;

	visionRadius = 100;
	maxForce = 0.02;

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

		//assert( (delta.x < 980 && delta.y < 570) );
		if (abs(delta.x) < visionRadius && abs(delta.y) < visionRadius) {
			if (size2(delta) < visionRadius*visionRadius && size2(delta) > 0) {

				targetAli += calcAlignment(tri);
				targetCoh += calcCohesion(delta);
				targetSep += calcSeparation(delta);

				count++;
			}
		}
	}

	if (count > 0) {
		sf::Vector2f deltaAli = normalise(targetAli) * alignment;
		sf::Vector2f deltaCoh = normalise(targetCoh )*cohesion;
		sf::Vector2f deltaSep = targetSep * separation;

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
		std::cout << "Alignment = " << alignment << std::endl;
		break;
	case ReynoldParameters::cohesion:
		cohesion += delta;
		std::cout << "Cohesion = " << cohesion << std::endl;
		break;
	case ReynoldParameters::separation:
		separation += delta;
		std::cout << "Separation = " << separation << std::endl;
		break;
	case ReynoldParameters::visionRadius:
		visionRadius += delta;
		std::cout << "VisionRadius = " << visionRadius << std::endl;
		break;
	case ReynoldParameters::maxForce:
		maxForce += delta;
		std::cout << "MaxForce = " << maxForce << std::endl;
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