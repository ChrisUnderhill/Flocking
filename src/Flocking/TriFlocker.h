#pragma once
#include <SFML/Graphics.hpp>

class TriFlocker
{
private:
	sf::Color color;
	sf::Color outColor;
	int outThickness;
	int size;

	sf::Vector2f pos;
	float angle;
	
	sf::ConvexShape triShape;
	sf::RenderWindow* window;

public:
	TriFlocker(int base, sf::Vector2f pos, sf::RenderWindow* win);
	virtual ~TriFlocker();

	void setColor(sf::Color col);
	void setOutColor(sf::Color col);
	void setThickness(int thick);
	void setSize(int s);

	void move(sf::Vector2f delta);
	void move(float deltax, float deltay);
	void rotate(float theta);
	void update();
	void draw();
};

