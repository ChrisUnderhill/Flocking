#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp> //need to link opengl manually to use

#include <iostream>
#include <random>
#include <vector>

#include <algorithm>
#include <numeric>
#include <future>

#include "TriFlocker.h"
#include "SimpleAimAt.h"
#include "SeeingBoids.h"
#include "AliCohSep.h"



template <typename RAIter>
void drawFlockers(RAIter beg, RAIter end, int lenAtOnce)
{
	auto len = end - beg;
	RAIter mid = beg + len / 2;


	
	if (len < lenAtOnce) {
		auto it = beg;
		for (int i = 1; i < lenAtOnce; i++) {
			(*it)->update();
			it = std::next(it);
			if (it == end)
				return;
		}
		return;
	}

	//std::for_each(beg, end, TriFlocker.update);

	auto handle = std::async(std::launch::async,
		drawFlockers<RAIter>, mid, end, lenAtOnce);

	drawFlockers(beg, mid, lenAtOnce);
	handle.get();

	return;
}


int main()
{
	srand(time(NULL));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Default, settings);

	std::vector<TriFlocker*> flockers;

	Steering* simpleSteer = new SimpleAimAt(&flockers);

	Steering* groupUp = new SeeingBoids(&flockers);

	Steering* Reynold = new AliCohSep(&flockers);

	//TriFlocker myFlocker(20, sf::Vector2f(50, 200), &window);

	//myFlocker.setSteering(Reynold);


	for (int i = 0; i < 100; i++) {
		flockers.push_back(new TriFlocker(20, sf::Vector2f(rand()%900, rand() % 900), &window));
		flockers[i]->initRandom();
		flockers[i]->setSteering(Reynold);
	}

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
					((AliCohSep*)Reynold)->setParameters(0.125f, 0.625f, 1.0f, 100.0f, 0.02f);
					break;

				case sf::Keyboard::Q:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::alignment, 0.05);
					break;
				case sf::Keyboard::A:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::alignment, -0.05);
					break;

				case sf::Keyboard::W:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::cohesion, 0.05);
					break;
				case sf::Keyboard::S:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::cohesion, -0.05);
					break;

				case sf::Keyboard::E:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::separation, 0.05);
					break;
				case sf::Keyboard::D:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::separation, -0.05);
					break;

				case sf::Keyboard::R:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::visionRadius, 20);
					break;
				case sf::Keyboard::F:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::visionRadius, -20);
					break;

				case sf::Keyboard::T:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::maxForce, 0.001);
					break;
				case sf::Keyboard::G:
					((AliCohSep*)Reynold)->changeParameter(AliCohSep::ReynoldParameters::maxForce, -0.001);
					break;

				case sf::Keyboard::Z:
				{
					for (int i = 0; i < 10; i++) {
						auto f = new TriFlocker(20, sf::Vector2f(rand() % 900, rand() % 900), &window);
						flockers.push_back(f);
						f->initRandom();
						f->setSteering(Reynold);
					}
					std::cout << "Num flockers = " << flockers.size() << std::endl;
					break;
				}
				case sf::Keyboard::X:
					for (int i = 0; i < 10; i++) {
						flockers.pop_back();
					}
					std::cout << "Num flockers = " << flockers.size() << std::endl;
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


		window.clear(sf::Color(255, 255, 255, 0));
		//myFlocker.move(0,0.1);


		//myFlocker.update();
		//myFlocker.draw();

		int numThreads = 16;

		drawFlockers(flockers.begin(), flockers.end(), (flockers.end()-flockers.begin())/numThreads );

		int count = 0;
		for (auto i : flockers) {
			//i->update();
			i->draw();
			//count++;
			//std::cout << i->getPos().x << " ";
		}
		//Sleep(1000);
		//std::cout << "\n";

		window.display();
	}

	return 0;
}