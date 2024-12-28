#ifndef _VIEW_H_
#define _VIEW_H_

#include <SFML/Graphics.hpp>



class GameView
{
public:
	sf::View* view;

	GameView()
	{
		view = new sf::View();
	}

	void update(float x, float y) { view->setCenter(x + 100, y - 100); }

	sf::View viewMap(float time)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			view->move(0.1 * time, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			view->move(0, 0.1 * time);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			view->move(-0.1 * time, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			view->move(0, -0.1 * time);
		}

		return *view;
	}

};




#endif
