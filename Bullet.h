#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "math.h"
class Bullet : public Entity
{
public:
	sf::Vector2f direct;
	sf::Vector2f char_vector;
	float vector_direction_length{ 0.0f };
	float distance{ 0.0f };
	float normal_vec_x;
	float normal_vec_y;
	sf::Vector2f temp_vec_dir;

	Bullet(sf::Image &image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H, sf::Vector2f direction) : Entity(image, Name, X, Y, W, H)
	{
		
		obj = lvl.getAllObjects();
		direct = direction;
		

		distance =  0.0f;

		temp_vec_dir.x = direct.x - x;
		temp_vec_dir.y = direct.y - y;

		vector_direction_length = sqrt((temp_vec_dir.x * temp_vec_dir.x) + (temp_vec_dir.y * temp_vec_dir.y));
		normal_vec_x = temp_vec_dir.x / vector_direction_length;
		normal_vec_y = temp_vec_dir.y / vector_direction_length;
	}

	sf::Sprite& getExMark()
	{
		sf::Sprite sp;

		return sp;
	}

	void update(float time)
	{
		if (name == "Bullet")
		{
			
			//distance = sqrt((direct.x - x) * (direct.x - x) + (direct.y - y) * (direct.y - y)); for RPG game
		
			x += normal_vec_x * time;
			y += normal_vec_y * time;

			if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
			if (y <= 0) y = 1;

			for (int i = 0; i < obj.size(); i++)
			{
				
				if (getRect().intersects(obj[i].rect) && obj[i].name == "solid")
				{
					life = false;
					isAnimationDeathEnd = true;
					
				}
				
			}

			sprite.setPosition(x + w / 2, y + h / 2);
		}
	}
};

#endif
