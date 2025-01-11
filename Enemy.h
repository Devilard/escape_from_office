#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"

class Enemy : public Entity
{
public:
	float currentFrame{0.0f};

	Enemy(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H, std::string qn, int ID);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time) override;
	void death(float time);
};

#endif