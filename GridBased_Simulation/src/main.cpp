// SFML
#include <SFML/Graphics.hpp>
// Other
#include <iostream>
#include <thread>
// My headers
#include "Headers/MainLoop.hpp"
#include "Headers/Common.hpp"
#include "Headers/Useful.hpp"
#include "Headers/Grid.hpp"

sf::RenderWindow* window;
sf::Vector2f windowSize;
sf::Font arial;
sf::Vector2i mousePos;

int main() {
	// window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	// creating window
	sf::RenderWindow Mainwindow(sf::VideoMode(800, 600), "Grid Simulation", sf::Style::Close, settings);
	window = &Mainwindow;
	setupWindow();
	hideConsole();

	// Getting random seed
	srand(time(0));

	// my main loop class
	Loop loop;

	Grid g(4);

	sf::Text fpsText;
	setupfps(&fpsText);

	sf::Clock FPSclock;
	unsigned int Frame = 0;
	// main loop
	while (Mainwindow.isOpen())
	{
		// processing inputs
		loop.Input();

		// updating window
		loop.Update();
		g.update();

		// rendering all objects
		//g.draw();
		fps(&fpsText, &FPSclock, &Frame);
		loop.Render();
	}
	return 0;
}
