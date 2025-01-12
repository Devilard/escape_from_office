#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include "iconvlite.h"

#include "level.h"
#include "Entity.h"
#include "Enemy.h"
#include "Mission.h"
#include "GameView.h"
#include "Player.h"
#include "Menu.h"
#include "NPC.h"
#include "QuestItem.h"

class Game
{
public:
	Menu* menu;
	GameView* view;
	TileMap* currentLevel;
	sf::Music* music;
	std::list<Entity*> entities;
	Object* PlayerObject;
	Player* player;
	sf::Image* heroImg;
	sf::Image* bulletImg;
	sf::Image* easyEnemyImg;
	sf::Image* angelEnemyImg;
	sf::Image* questItemImg;
	std::vector<Object> enemiesA;
	std::vector<Object> enemies;
	std::vector<Object> users;
	std::vector<Object> collectables;
	sf::Image* userImg;
	sf::Font* font;
	sf::Text* missionText;
	sf::Image* missionBgImg;
	sf::Texture* missionTexture;
	sf::Sprite* missionSprite;
	bool isShowMission;
	Mission* mission;
	int levelNumber;

	Game();
	void loadAll();
	void showMenu(sf::RenderWindow& window) { menu->menu(window, *font); }
	void fillEntitiesList();
	void changeLevel(int nl);
	TileMap& getCurrentLevel() { return *currentLevel; }
	Object& getPlayerObject() { return *PlayerObject; }
	std::list<Entity*>& getEntities() { return entities; }
	Player& getPlayer() { return *player; }
	GameView* getGameView() { return view; }
	void showMission();
	void hideMission();
	void update(float time);
	void Loop(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight);
	void processInput(sf::RenderWindow& window, sf::Vector2f pos);
	void render(sf::RenderWindow& window, std::list<Entity*>::iterator& it);
	

private:
	void entitiesUpdate(float time);

};


#endif