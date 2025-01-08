#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SFML/Graphics.hpp>
#include "level.h"
class Entity
{
public:
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	std::vector<Object> obj;
	bool isAnimationDeathEnd;
	float deathAnimationTimer;
	bool isHaveQuest;

	Entity(sf::Image &image, sf::String Name,float X, float Y, int W, int H)
	{
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0; isAnimationDeathEnd = false;
		life = true; onGround = false; isMove = false; deathAnimationTimer = 0.0f;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
		isHaveQuest = false;
	}

	sf::FloatRect getRect()
	{
		return sf::FloatRect(x,y,w,h);
	}

	virtual void update(float time) = 0;
	virtual sf::Sprite& getExMark() = 0;
};


#endif