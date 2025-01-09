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

	Entity(sf::Image &image, sf::String Name,float X, float Y, float W, float H)
	{
		img = image;
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0; id = 0;
		speed = 0; health = 100; dx = 0; dy = 0; isAnimationDeathEnd = false;
		life = true; onGround = false; isMove = false; deathAnimationTimer = 0.0f;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2.0f, h / 2.0f);
		isHaveQuest = false;
	}


	sf::FloatRect getRect()
	{
		return sf::FloatRect(x,y,w,h);
	}

	virtual void update(float time) {};
	virtual sf::Sprite& getExMark() { return sprite; };
};


#endif