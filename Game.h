#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>

#include "level.h"
#include "Entity.h"
#include "Enemy.h"

class Game
{
	
public:
	TileMap* currentLevel;

	std::list<Entity*> entities;

	Object* PlayerObject;
	Player* player;
	sf::Image* heroImg;
	
	sf::Image* bulletImg;

	sf::Image* easyEnemyImg;
	std::vector<Object> enemies;
	std::vector<Object> users;
	
	sf::Image* userImg;

	Game(TileMap* level)
	{
		currentLevel = level;

		//init player
		heroImg = new sf::Image;
		heroImg->loadFromFile("layouts/img/hero.png");
		
		PlayerObject = new Object(level->getObject("Player"));
		
		
		player = new Player(*heroImg, "Player1", *currentLevel, getPlayerObject().rect.left, getPlayerObject().rect.top, 64.0f, 64.0f);
		

		bulletImg = new sf::Image();
		bulletImg->loadFromFile("layouts/img/bullet.png");

		easyEnemyImg = new sf::Image;
		easyEnemyImg->loadFromFile("layouts/img/shamaich.png");
		easyEnemyImg->createMaskFromColor(sf::Color(255, 0, 0));

		userImg = new sf::Image;
		userImg->loadFromFile("layouts/img/first_user.png");

		enemies = currentLevel->getObjectsByName("easyEnemy");
		users = currentLevel->getObjectsByName("User");

		//Filling the enemy list
		for (int i = 0; i < enemies.size(); i++)
		{
			entities.push_back(new Enemy(*easyEnemyImg, "EasyEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 200, 97));
		}

		for (int i = 0; i < users.size(); i++)
		{
			entities.push_back(new Enemy(*userImg, "User", *currentLevel, users[i].rect.left, users[i].rect.top, 64, 64));
		}
	}

	TileMap& getCurrentLevel()
	{
		return *currentLevel;
	}

	Object& getPlayerObject()
	{
		return *PlayerObject;
	}

	std::list<Entity*>& getEntities()
	{
		return entities;
	}

	void update(float time)
	{

		player->update(time);
		entitiesUpdate(time);

	}

	Player& getPlayer()
	{
		return *player;
	}

private:

	void entitiesUpdate(float time)
	{
		std::list<Entity*>::iterator it;
		std::list<Entity*>::iterator it2;
		for (it = entities.begin(); it != entities.end();)
		{
			Entity* b = *it;
			b->update(time);
			if (b->life == false && b->isAnimationDeathEnd == true)
			{
				it = entities.erase(it); delete b;
			}
			else { it++; }
		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			if ((*it)->getRect().intersects(player->getRect()))
			{
				if ((*it)->name == "EasyEnemy") {

					if ((player->dy > 0) && (player->onGround == false)) { (*it)->dx = 0; player->dy = -0.2f; (*it)->health = 0; }
					else {
						player->health -= 5;
					}
				}
			}

			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())
				{
					if ((*it)->getRect().intersects((*it2)->getRect()) && (*it)->name == "EasyEnemy" && (*it2)->name == "Bullet")
					{
						(*it)->health = 0;
						(*it2)->life = false;
						(*it2)->isAnimationDeathEnd = true;
						break;
					}
				}
			}
		}
	}


};

#endif