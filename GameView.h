#ifndef _VIEW_H_
#define _VIEW_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class GameView
{
public:
	sf::View* view;

	GameView() { view = new sf::View(); }
	void update(float x, float y);
	sf::View viewMap(float time);

};

#endif
