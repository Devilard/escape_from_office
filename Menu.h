

#include <string>
#include <sstream>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "level.h"
#include "Entity.h"
#include "Enemy.h"
#include "Mission.h"
#include "GameView.h"
#include "Player.h"


using namespace sf;

void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("layouts/img/menu/111.png");
	menuTexture2.loadFromFile("layouts/img/menu/222.png");
	menuTexture3.loadFromFile("layouts/img/menu/333.png");
	aboutTexture;
	menuBackground.loadFromFile("layouts/img/menu/bg.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBG(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 30);
	menu3.setPosition(100, 30);
	menuBG.setPosition(345, 30);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);

		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}
		window.draw(menuBG);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();


	}
}


