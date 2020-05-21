
//#include "pch.h"

#include "SFML/Graphics.hpp"

using namespace sf;

int main()
{
	// lage video modus objekt
	sf::VideoMode vm(1920, 1080);
	// Lage og åpne et vindu for the game renderwindow
	sf::RenderWindow window(vm, "Timber!!", sf::Style::Default);
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		window.clear();
		window.display();
	}


	return 0;
}