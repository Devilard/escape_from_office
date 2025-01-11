#ifndef _MENU_H_
#define _MENU_H_

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "iconvlite.h"

class Menu
{
public:
	Menu() = default;

	void menu(sf::RenderWindow& window, sf::Font& font);

};

#endif
