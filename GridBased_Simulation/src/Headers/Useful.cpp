#include "Useful.hpp"
#include <iostream>

void setupfps(sf::Text* fpsText) {
	fpsText->setFont(arial);
	fpsText->setFillColor(sf::Color::Red);
	fpsText->setCharacterSize(24);
}
void fps(sf::Text* fpsText, sf::Clock* clock, unsigned int* Frame)
{
	if (clock->getElapsedTime().asSeconds() >= 1.f)
	{
		int FPS = *Frame;
		*Frame = 0;
		clock->restart();

		fpsText->setString("FPS: " + std::to_string(FPS));
	}
	++ *Frame;
	window->draw(*fpsText);
}

void setupWindow()
{
	showConsole();

	window->setPosition(window->getPosition() - sf::Vector2i(0, 50));
	//window->setVerticalSyncEnabled(true);

	std::cout << "Set your fps limit: ";
	int fpsLimit;
	std::cin >> fpsLimit;
	std::cout << std::endl;
	window->setFramerateLimit(abs(fpsLimit));

	windowSize = sf::Vector2f(window->getSize());
	arial.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}

int rand50()
{
	// rand() function will generate odd or even
	// number with equal probability. If rand()
	// generates odd number, the function will
	// return 1 else it will return 0.
	return rand() & 1;
}