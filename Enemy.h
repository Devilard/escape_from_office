#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
#include "Player.h"


class Enemy : public Entity
{
public:
	float currentFrame{0.0f};
	sf::Texture* exMarkTexture;
	sf::Sprite* exMarkSprite;
	std::string questName;
	Enemy(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y,  int W, int H, std::string qn) : Entity(image, Name, X, Y, W, H)
	{
		questName = qn;
		exMarkTexture = new sf::Texture;
		exMarkTexture->loadFromFile("layouts/img/exclamation_mark.png");
		exMarkSprite = new sf::Sprite;
		exMarkSprite->setTexture(*exMarkTexture);
		exMarkSprite->setTextureRect(sf::IntRect(12, 0, 7, 28));
		
		obj = lvl.getObjectsByName("solid");
		currentFrame = 0.0f;
		if (name == "EasyEnemy")
		{
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
			dx = 0.1f;
			
			if (currentFrame > 5) currentFrame -= 4;
			sprite.setTextureRect(sf::IntRect(((76 * (int)currentFrame)), 0, -78, 75));
		}
		
		if (name == "User")
		{
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{

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
				if (currentFrame >= 4) currentFrame -= 3;
				sprite.setTextureRect(sf::IntRect(((30 * (int)currentFrame) ), 1, 30, 72));
				if (questName != "")
				{
					isHaveQuest = true;
				}
			}
			if (name == "EasyEnemy")
			{
				currentFrame += 0.005f * time;
				if (currentFrame >= 4) currentFrame -= 3;
				sprite.setTextureRect(sf::IntRect(((78 * (int)currentFrame)), 0, -78, 75));
			}
			checkCollisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2);
			exMarkSprite->setPosition(x + 15, y - 40);
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

	void setQuest()
	{
		
	}

	sf::Sprite& getExMark()
	{
		return *exMarkSprite;
	}
};

#endif