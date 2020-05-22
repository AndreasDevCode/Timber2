
//#include "pch.h"

#include "SFML/Graphics.hpp"
#include <sstream>
using namespace sf;

int main()
{
	// lage video modus objekt
	sf::VideoMode vm(1920, 1080);
	// Lage og åpne et vindu for the game renderwindow
	sf::RenderWindow window(vm, "Timber!!", sf::Style::Fullscreen);
	Texture textureBackground;
	Texture textureTree;
	Texture textureBee;
	Texture textureCloud;
	
	textureBackground.loadFromFile("graphics/background.png");
	textureTree.loadFromFile("graphics/tree.png");
	textureBee.loadFromFile("graphics/bee.png");
	textureCloud.loadFromFile("graphics/cloud.png");

	Sprite spriteBackground;
	Sprite spriteTree;
	Sprite spriteBee;
	Sprite spriteCloud1, spriteCloud2, spriteCloud3;

	spriteBackground.setTexture(textureBackground);
	spriteTree.setTexture(textureTree);
	spriteBee.setTexture(textureBee);
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	spriteBackground.setPosition(0,0);
	spriteTree.setPosition(810,0);
	spriteBee.setPosition(500,900);
	spriteCloud1.setPosition(100,100);
	spriteCloud2.setPosition(500,200);
	spriteCloud3.setPosition(1200,100);

	bool beeActive = false;					// decides if bee is moving
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float beeSpeed = 0.0f;					// bee speed
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	Clock clock;

	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920/2) - timeBarStartWidth/2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	bool pause = false;

	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press enter to start!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// position the texts

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920/2.0f, 1080/2.0f);
	scoreText.setPosition(20, 20);
	while (window.isOpen())
	{
		/*
					Handle input
		*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			score = 0;
			timeRemaining = 5.0f;
			pause = !pause;
		}
		/*
					Update the scene		
		*/
		if (!pause)
		{
			Time dt = clock.restart();
			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				pause = true;
				messageText.setString("Time is out!!!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
										textRect.width /2.0f,
										textRect.top +
										textRect.height / 2.0f);
				messageText.setPosition(1920/2.0f,1080/2.0f);
			}


			if (!beeActive)
			{
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200.0f;

				srand((int)time(0)*10);
				float height = (rand() % 500) + 500.0f;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition( spriteBee.getPosition().x - (beeSpeed*dt.asSeconds()),
										spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < - 100)
				{
					beeActive = false;
				}
			}
			if (!cloud1Active)
			{
				srand((int)time(0) * 10);
				cloud1Speed = float(rand() % 200);

				srand((int)time(0) * 10);
				float height = float(rand() % 150);
				spriteCloud1.setPosition(-500, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);
				if (spriteCloud1.getPosition().x > 2220)
				{
					cloud1Active = false;
				}
			}
			if (!cloud2Active)
			{
				srand((int)time(0) * 20);
				cloud2Speed = float(rand() % 200);

				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150.0f;
				spriteCloud2.setPosition(-700, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);
				if (spriteCloud2.getPosition().x > 2220)
				{
					cloud2Active = false;
				}
			}
			if (!cloud3Active)
			{
				srand((int)time(0) * 30);
				cloud3Speed = float(rand() % 200);

				srand((int)time(0) * 30);
				float height = (rand() % 450) -150.0f ;
				spriteCloud3.setPosition(-300, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);
				if (spriteCloud3.getPosition().x > 2220)
				{
					cloud3Active = false;
				}
			}
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		}
		/*
					Draw the scene
		*/
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		window.draw(scoreText);
		window.draw(timeBar);
		if (pause)
		{
			window.draw(messageText);
		}
		window.display();
	}


	return 0;
}