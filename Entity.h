#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SFML/Graphics.hpp>
#include "level.h"

class Entity
{
public:
	float dx, dy, x, y, speed, moveTimer;
	float w, h, health;
	bool life, isMove, onGround;
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	std::vector<Object> obj;
	bool isAnimationDeathEnd;
	float deathAnimationTimer;
	bool isHaveQuest;
	int id;

	Entity(sf::Image& image, sf::String Name, float X, float Y, float W, float H);
	sf::FloatRect getRect();
	virtual void update(float time) {};
	virtual sf::Sprite& getExMark() { return sprite; };
};


#endif