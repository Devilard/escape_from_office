#include "Entity.h"

Entity::Entity(sf::Image& image, sf::String Name, float X, float Y, float W, float H)
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

sf::FloatRect Entity::getRect()
{
	return sf::FloatRect(x, y, w, h);
}