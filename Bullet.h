#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "math.h"
class Bullet : public Entity
{
public:
	sf::Vector2f direct;
	sf::Vector2f char_vector;
	float distance{ 0.0f };
	Bullet(sf::Image &image, sf::String Name, TileMap& lvl, float X, float Y, int W, int H, sf::Vector2f direction) : Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.getObjectsByName("solid");

		direct = direction;

		distance =  0.0f;
	}

	void update(float time)
	{

		distance = sqrt((direct.x - x)*(direct.x -x) + (direct.y - y) * (direct.y - y));
		
		
		
		x += 0.2 * time * (direct.x - x) / distance;
		y += 0.2 * time * (direct.y - y) / distance;


		for (int i = 0; i < obj.size(); i++)
		{
			if (getRect().intersects(obj[i].rect))
			{
				life = false;
			}
		}

		sprite.setPosition(x + w/2, y + h/2);
	}
};

#endif
