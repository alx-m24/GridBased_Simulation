#include "MainLoop.hpp"

void Loop::Input() {
	sf::Event event;
	// processing sfml events
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: {
			window->close();
			break;
		}
		case sf::Event::MouseMoved: {
			mousePos = sf::Mouse::getPosition(*window);
			break;
		}
		case sf::Event::Resized: {
			sf::View view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
			window->setView(view);
			windowSize = sf::Vector2f(window->getSize());
			break;
		}
		default:
			break;
		}
	}
}

void Loop::Update()
{
	window->clear(sf::Color::Black);
}

void Loop::Render()
{
	window->display();
}