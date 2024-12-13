#ifndef _VIEW_H_
#define _VIEW_H_

#include <SFML/Graphics.hpp>

sf::View view;


sf::View getPlayerCoordinateForView(float x, float y)
{
	view.setCenter(x+100, y-100);

	return view;
}

sf::View viewMap(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(0.1 * time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(0, 0.1 * time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(-0.1 * time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0, -0.1 * time);
	}

	return view;
}

#endif
