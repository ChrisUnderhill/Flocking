#pragma once
#include <SFML/Graphics.hpp>
#include "Steering.h"

class TriFlocker
{
private:
	//Appeareance
	sf::Color color;
	sf::Color outColor;
	int outThickness;
	int size;

	//Physics
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	float angle;
	
	//SFML
	sf::ConvexShape triShape;
	sf::RenderWindow* window;

	//Movement
	void move(sf::Vector2f delta);
	void move(float deltax, float deltay);
	void rotate(float theta);
	Steering* steering;

public:
	TriFlocker(sf::RenderWindow* win);
	TriFlocker(int base, sf::Vector2f pos, sf::RenderWindow* win);
	virtual ~TriFlocker();


	//Appearance
	void setColor(sf::Color col);
	void setOutColor(sf::Color col);
	void setThickness(int thick);
	void setSize(int s);


	void setSteering(Steering* s);
	void initRandom();

	//Drawing
	void update();
	void draw();
};
