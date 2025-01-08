#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <sstream>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "level.h"
#include "Entity.h"
#include "Enemy.h"
#include "Mission.h"
#include "GameView.h"
#include "Player.h"

class Game
{
	
public:
	GameView* view;
	TileMap* currentLevel;
	sf::Music* music;

	std::list<Entity*> entities;

	Object* PlayerObject;
	Player* player;
	sf::Image* heroImg;
	
	sf::Image* bulletImg;

	sf::Image* exclamationMarkImg;

	sf::Image* hardEnemyImg;
	sf::Image* easyEnemyImg;
	sf::Image* angelEnemyImg;
	std::vector<Object> enemiesA;
	std::vector<Object> enemiesH;
	std::vector<Object> enemies;
	std::vector<Object> users;
	std::vector<Object> doors;
	std::vector<Object> mark;

	
	sf::Image* userImg;

	sf::Font* font;
	sf::Text* missionText;

	sf::Image* missionBgImg;
	sf::Texture* missionTexture;
	sf::Sprite* missionSprite;

	bool isShowMission;

	Mission* mission;
	int levelNumber;

	Game()
	{
		view = new GameView();
		music = new sf::Music();
		font = new sf::Font();
		missionText = new sf::Text();
		missionBgImg = new sf::Image;
		missionTexture = new sf::Texture();
		missionSprite = new sf::Sprite();
		mission = new Mission();
		currentLevel = new TileMap();
		heroImg = new sf::Image;
		bulletImg = new sf::Image();
		easyEnemyImg = new sf::Image;
		angelEnemyImg = new sf::Image;
		hardEnemyImg = new sf::Image;
		exclamationMarkImg = new sf::Image;
		userImg = new sf::Image;
		isShowMission = true;
		levelNumber = 1;
	}

	void loadAll()
	{
		//Load Music and start play
		music->openFromFile("sound/Powerfu_Trap.mp3");
		music->setVolume(4.0f);
		music->play();
		music->setLoop(true);

		//Load font
		font->loadFromFile("CyrilicOld.TTF");

		//Set the initial value for the text
		missionText->setString("");
		missionText->setCharacterSize(20);
		missionText->setFont(*font);
		sf::Color redColor;
		missionText->setFillColor(sf::Color::Red);

		//Load mission background image, texture, sprite
		missionBgImg->loadFromFile("layouts/img/missionbg.png");
		missionBgImg->createMaskFromColor(sf::Color(0, 0, 0));
		missionTexture->loadFromImage(*missionBgImg);
		missionSprite->setTexture(*missionTexture);
		missionSprite->setTextureRect(sf::IntRect(0, 0, 1024, 1200));
		missionSprite->setScale(0.35f, 0.35f);

		changeLevel(1);
		
		//Load exclamation_mark
		exclamationMarkImg->loadFromFile("layouts/img/exclamation_mark.png");
		exclamationMarkImg->createMaskFromColor(sf::Color(255, 0, 0));

		mark = currentLevel->getObjectsByName("exclamationMark");
		

		//Load hero
		heroImg->loadFromFile("layouts/img/office_man.png");
		PlayerObject = new Object(currentLevel->getObject("Player"));
		player = new Player(*heroImg, "Player1", *currentLevel, getPlayerObject().rect.left, getPlayerObject().rect.top, 36.0f, 75.0f);

		//Load bullet
		bulletImg->loadFromFile("layouts/img/bullet.png");

		//Load user
		userImg->loadFromFile("layouts/img/first_user_v2.png");

		//Load enemy
		easyEnemyImg->loadFromFile("layouts/img/shamaich2.png");
		easyEnemyImg->createMaskFromColor(sf::Color(255, 0, 0));

		hardEnemyImg->loadFromFile("layouts/img/shamaich2.png");
		hardEnemyImg->createMaskFromColor(sf::Color(255, 0, 0));

		angelEnemyImg->loadFromFile("layouts/img/angel.png");
		angelEnemyImg->createMaskFromColor(sf::Color(255, 0, 0));

		enemiesH = currentLevel->getObjectsByName("hardEnemy");
		enemies = currentLevel->getObjectsByName("easyEnemy");
		users = currentLevel->getObjectsByName("User");
		doors = currentLevel->getObjectsByType("door");
		enemiesA = currentLevel->getObjectsByName("angelEnemy");


		//Filling the enemy list
		for (int i = 0; i < enemies.size(); i++)
		{
			entities.push_back(new Enemy(*easyEnemyImg, "EasyEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 78, 65));
		}

		for (int i = 0; i < enemiesA.size(); i++)
		{
			entities.push_back(new Enemy(*angelEnemyImg, "EasyEnemy", *currentLevel, enemiesA[i].rect.left, enemiesA[i].rect.top, 78, 65));
		}

		for (int i = 0; i < users.size(); i++)
		{
			entities.push_back(new Enemy(*userImg, "User", *currentLevel, users[i].rect.left, users[i].rect.top, 64, 64));
		}
		for (int i = 0; i < mark.size(); i++)
		{
			entities.push_back(new Enemy(*exclamationMarkImg, "User", *currentLevel, mark[i].rect.left, mark[i].rect.top, 32, 32));
		}
	}

	void changeLevel(int nl)
	{
		levelNumber = nl;
		switch (levelNumber)
		{
			case 1:
			{
				currentLevel->clearLevel();
				currentLevel->load("tiled_prod/map.tmx");
				break;
			}
			
			case 2: 
			{
				entities.clear();
				currentLevel->clearLevel();

				currentLevel->load("tiled_prod/level_2.tmx");
				delete PlayerObject;
				PlayerObject = new Object(currentLevel->getObject("Player"));
				player->x = getPlayerObject().rect.left;
				player->y = getPlayerObject().rect.top;
				
				break;
			}
		}
	}
		//Filling the hardEnemy list Добавить нового врага 
		/*for (int i = 0; i < enemiesH.size(); i++)
		{
		entities.push_back(new Enemy2(*hardEnemyImg, "HardEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 200, 97));
		}

		for (int i = 0; i < users.size(); i++)
		{
		entities.push_back(new Enemy2(*userImg, "User", *currentLevel, users[i].rect.left, users[i].rect.top, 64, 64));
		}
		*/


	TileMap& getCurrentLevel() { return *currentLevel; }
	Object& getPlayerObject() { return *PlayerObject; }
	std::list<Entity*>& getEntities() { return entities; }
	Player& getPlayer() { return *player; }

	GameView* getGameView()
	{
		return view;
	}

	void showMission()
	{
		std::ostringstream playerHealthString;
		playerHealthString << getPlayer().health;
		std::ostringstream missionTextString;
		missionTextString << mission->getTextMission(mission->getCurrentMisson(getPlayer().getPlayerCoordinateX()));
		missionText->setString("Здоровье: " + playerHealthString.str() + "\n" + missionTextString.str());
		missionSprite->setPosition(getGameView()->view->getCenter().x + 115, getGameView()->view->getCenter().y - 130);
		isShowMission = false;
	}

	void hideMission()
	{
		missionText->setString("");
		isShowMission = true;
	}



	void update(float time)
	{
		player->update(time);
		entitiesUpdate(time);
		getGameView()->update(player->x, player->y);
	}

	void Loop(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight)
	{
		getGameView()->view->reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
		std::list<Entity*>::iterator it;
		float currentFrame{ 0.0f };
		sf::Clock clock;


		while (window.isOpen())
		{
			float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
			clock.restart();

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f pos = window.mapPixelToCoords(pixelPos);


			time = time / 800;

			pollEvent(window, pos);


			update(time);
			window.setView(*(getGameView()->view));


			getGameView()->viewMap(time);

			render(window, it);

		}

	}

	void pollEvent(sf::RenderWindow& window, sf::Vector2f pos)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Tab)
				{
					switch (isShowMission) {

					case true: {
						showMission();
						break;

					}
					case false: {
						hideMission();
						break;
					}
					}
				}

				if (event.key.code == sf::Keyboard::E)
				{
					if (player->isActionKeyPressed)
					{
						player->action();
					}
					
				}

				if (event.key.code == sf::Keyboard::L)
				{
					
					changeLevel(2);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{

					getPlayer().shoot(getEntities(), pos, bulletImg, currentLevel);
				}
			}


		}
	}

	void render(sf::RenderWindow& window, std::list<Entity*>::iterator& it)
	{
		window.clear();
		window.draw(getCurrentLevel());
		for (it = getEntities().begin(); it != getEntities().end(); it++) { window.draw((*it)->sprite); }
		window.draw(getPlayer().sprite);

		/*
		std::ostringstream playerScoreString;
		playerScoreString << p.health;

		text.setString("Собранно камней " + playerScoreString.str());
		text.setPosition(view.getCenter().x - 200, view.getCenter().y - 200);
		*/

		if (!isShowMission)
		{
			window.draw(*missionSprite);
			window.draw(*missionText);
			missionText->setPosition(getGameView()->view->getCenter().x + 190, getGameView()->view->getCenter().y - 50);
			missionSprite->setPosition(getGameView()->view->getCenter().x + 115, getGameView()->view->getCenter().y - 130);

		}

		window.display();
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
						player->dy = -0.4f;
						player->dx = -0.4f;
						
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