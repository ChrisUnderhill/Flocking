#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				break;
			case sf::Event::LostFocus:
				//pause
				break;
			case sf::Event::GainedFocus:
				//resume
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Return:
					//pause
					break;
				}
				break;
			case sf::Event::KeyReleased:
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					float delta = event.mouseWheelScroll.delta;
					//increase number of flockers
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//add an obstacle maybe
				} else if (event.mouseButton.button == sf::Mouse::Right) {
					//remove an obstacle maybe
				}
				break;
			case sf::Event::MouseButtonReleased:
				break;
			case sf::Event::MouseMoved:
				break;

			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}