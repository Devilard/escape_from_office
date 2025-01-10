#ifndef _MENU_H_
#define _MENU_H_

#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu() = default;

	void menu(sf::RenderWindow& window, sf::Font& font) {

		sf::Text* menuStartGame = new sf::Text("Начать игру", font, 30);
		sf::Text* menuAbout = new sf::Text("Об Игре", font, 30);
		sf::Text* menuExit = new sf::Text("Выход", font, 30);

		sf::Texture aboutTexture, menuBackground;
		aboutTexture.loadFromFile("layouts/img/menu/about.png");
		menuBackground.loadFromFile("layouts/img/menu/bg.png");
		sf::Sprite about(aboutTexture), menuBG(menuBackground);
		bool isMenu = true;
		int menuNum = 0;

		menuStartGame->setPosition(100, 50);
		menuAbout->setPosition(100, 150);
		menuExit->setPosition(100, 300);
		menuBG.setPosition(-545, -260);

		window.clear(sf::Color(129, 181, 221));

		while (isMenu)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) { window.close(); }

				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						if (menuNum == 1) { isMenu = false; }

						if (menuNum == 2)
						{ 
							bool showAbout = true;
							while (showAbout)
							{
								window.draw(about);
								window.display();
								sf::Event event2;
								while (window.pollEvent(event2))
								{
									if (event2.type == sf::Event::KeyPressed)
									{
										if (event.type == sf::Event::Closed) { window.close(); }

										if (event2.key.code == sf::Keyboard::Escape)
										{
											showAbout = false;
										}
									}
								}
							}	
						}
						if (menuNum == 3) { window.close(); isMenu = false; }

					}
				}

				if (event.type == sf::Event::MouseMoved)
				{
					menuStartGame->setFillColor(sf::Color::White);
					menuAbout->setFillColor(sf::Color::White);
					menuExit->setFillColor(sf::Color::White);

					if (sf::IntRect(100, 50, 300, 50).contains(sf::Mouse::getPosition(window))) { menuStartGame->setFillColor(sf::Color::Blue); menuNum = 1; }
					if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { menuAbout->setFillColor(sf::Color::Blue); menuNum = 2; }
					if (sf::IntRect(100, 300, 300, 50).contains(sf::Mouse::getPosition(window))) { menuExit->setFillColor(sf::Color::Blue); menuNum = 3; }

				}
			}


			window.draw(menuBG);
			window.draw(*menuStartGame);
			window.draw(*menuAbout);
			window.draw(*menuExit);


			window.display();
		}
	}
};

#endif
