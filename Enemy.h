#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"


class Enemy : public Entity
{
public:
	float currentFrame;
	Enemy(sf::Image &image, sf::String Name, TileMap& lvl, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.getObjectsByName("solid");

		if (name == "EasyEnemy")
		{
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
			dx = 0.1f;
			currentFrame = 1.0f;
		}

		if (name == "User")
		{
			std::cout << "User\n";
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		/*
		for (int i = y / 32; i < (y + h) / 32; i++)
		{
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
				{
					if (Dy > 0) { y = i * 32 - h; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
					if (Dy < 0) { y = i * 32 + 32; }//столкновение с верхними краями карты(может и не пригодиться)
					if (Dx > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//с правым краем карты
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// с левым краем карты
				}
			}
		}
		*/

		for (int i = 0; i < obj.size(); i++)
		{
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1f; sprite.scale(-1, 1); }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1f; sprite.scale(-1, 1); }
				}
			}
		}
	}

	void update(float time)
	{
		if (name == "EasyEnemy" || name == "User")
		{
			if (name == "User")
			{
				currentFrame += 0.005f * time;
				if (currentFrame >= 14) currentFrame -= 13;
				sprite.setTextureRect(sf::IntRect(((30 * (int)currentFrame) ), 1, 30, 72));
			}
			checkCollisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }

			if (life == false)
			{
				sprite.setColor(sf::Color::Red);
				deathAnimationTimer += time;
				if (deathAnimationTimer > 100)
				{
					isAnimationDeathEnd = true;
				}
			}
		}
	}

};

#endif