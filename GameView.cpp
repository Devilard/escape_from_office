#include "GameView.h"

void GameView::update(float x, float y)
{
	if (x < 540) { x = 540; }
	if (x > 3820) { x = 3820; }
	if (y > 3650) { y = 3650; }
	view->setSize(1500, 1200);
	view->setCenter(x + 100, y - 100);
}

sf::View GameView::viewMap(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		view->move(0.1f * time, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		view->move(0.0f, 0.1f * time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		view->move(-0.1f * time, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		view->move(0.0f, -0.1f * time);
	}

	return *view;
}