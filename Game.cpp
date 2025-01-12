#include "Game.h"


Game::Game()
{
	menu = new Menu();
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
	userImg = new sf::Image;
	isShowMission = true;
	levelNumber = 1;
	questItemImg = new sf::Image;
}

void Game::loadAll()
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
	missionText->setFillColor(sf::Color::Red);

	//Load mission background image, texture, sprite
	missionBgImg->loadFromFile("layouts/img/missionbg.png");
	missionBgImg->createMaskFromColor(sf::Color(0, 0, 0));
	missionTexture->loadFromImage(*missionBgImg);
	missionSprite->setTexture(*missionTexture);
	missionSprite->setTextureRect(sf::IntRect(0, 0, 1024, 1200));
	missionSprite->setScale(0.35f, 0.35f);

	changeLevel(1);

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

	angelEnemyImg->loadFromFile("layouts/img/angel.png");
	angelEnemyImg->createMaskFromColor(sf::Color(255, 0, 0));

	questItemImg->loadFromFile("layouts/img/qa_mouse.png");

	enemies = currentLevel->getObjectsByName("easyEnemy");
	users = currentLevel->getObjectsByName("User");
	enemiesA = currentLevel->getObjectsByName("angelEnemy");
	collectables = currentLevel->getObjectsByType("collectable");

	

	mission->readQuestFromJson();

	fillEntitiesList();

}

void Game::fillEntitiesList()
{
	//Filling the enemy list
	for (int i = 0; i < enemies.size(); i++)
	{
		std::string questName = enemies[i].GetPropertyString("QuestName");
		if (questName != "")
		{
			entities.push_back(new Enemy(*easyEnemyImg, "EasyEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 78, 65, questName, enemies[i].id));
		}
		else
		{
			entities.push_back(new Enemy(*easyEnemyImg, "EasyEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 78, 65, questName, enemies[i].id));
		}

	}

	for (int i = 0; i < enemiesA.size(); i++)
	{
		std::string questName = "";
		entities.push_back(new Enemy(*angelEnemyImg, "EasyEnemy", *currentLevel, enemiesA[i].rect.left, enemiesA[i].rect.top, 78, 65, questName, enemiesA[i].id));
	}

	for (int i = 0; i < users.size(); i++)
	{
		std::string questName = users[i].GetPropertyString("QuestName");
		if (questName != "")
		{
			entities.push_back(new NPC(*userImg, "User", *currentLevel, users[i].rect.left, users[i].rect.top, 64, 64, questName, users[i].id, mission));
		}
		else
		{
			entities.push_back(new NPC(*userImg, "User", *currentLevel, users[i].rect.left, users[i].rect.top, 64, 64, "", users[i].id, mission));
		}

	}

	for (int i = 0; i < collectables.size(); i++)
	{
		entities.push_back(new QuestItem(*questItemImg, "questItem", *currentLevel, collectables[i].rect.left, collectables[i].rect.top, 16, 16));
	}
}

void Game::changeLevel(int nl)
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

void Game::showMission()
{
	std::ostringstream playerHealthString;
	playerHealthString << getPlayer().health;
	std::ostringstream missionTextString;
	missionTextString << mission->getTextMission(mission->getCurrentMisson(static_cast<int>(getPlayer().getPlayerCoordinateX())));
	//missionText->setString("«доровье: " + playerHealthString.str() + "\n" + missionTextString.str());

	if (!getPlayer().questList.empty())
	{
		std::map<std::string, Quest>::iterator it;
		it = getPlayer().questList.begin();
		
		missionText->setString(it->second.questName + "\n" + it->second.questDescription);
	}
	else
	{
		missionText->setString("");
	}
	missionSprite->setPosition(getGameView()->view->getCenter().x + 115, getGameView()->view->getCenter().y - 130);
	isShowMission = false;
}

void Game::hideMission()
{
	missionText->setString("");
	isShowMission = true;
}

void Game::update(float time)
{
	player->update(time);
	entitiesUpdate(time);
	getGameView()->update(player->x, player->y);
}

void Game::Loop(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight)
{
	getGameView()->view->reset(sf::FloatRect(0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
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

		processInput(window, pos);


		update(time);
		window.setView(*(getGameView()->view));


		getGameView()->viewMap(time);

		render(window, it);

	}

}

void Game::processInput(sf::RenderWindow& window, sf::Vector2f pos)
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
					player->action(getEntities());
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

void Game::render(sf::RenderWindow& window, std::list<Entity*>::iterator& it)
{
	window.clear();
	window.draw(getCurrentLevel());
	for (it = getEntities().begin(); it != getEntities().end(); it++)
	{
		window.draw((*it)->sprite);
		if ((*it)->isHaveQuest)
		{
			window.draw((*it)->getExMark());
		}
	}
	window.draw(getPlayer().sprite);

	/*
	std::ostringstream playerScoreString;
	playerScoreString << p.health;

	text.setString("—обранно камней " + playerScoreString.str());
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

void Game::entitiesUpdate(float time)
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

	bool isCollect = false;

	for (it = entities.begin(); it != entities.end();)
	{
		isCollect = false;

		if ((*it)->getRect().intersects(player->getRect()))
		{
			if ((*it)->name == "EasyEnemy")
			{

				if ((player->dy > 0) && (player->onGround == false)) { (*it)->dx = 0; player->dy = -0.2f; (*it)->health = 0; }
				else {

					player->dx = -10.0f;

					player->health -= 5;
				}
			}

			if ((*it)->name == "questItem")
			{
				std::string qn = static_cast<QuestItem&>(*(*it)).questName;
				if (player->questList[qn].status == statuses::taken)
				{
					player->questList[qn].status = statuses::wait_execution;
					isCollect = true;
				}
			}

		}

		if (isCollect == false)
		{
			it++;
		}
		else
		{
			it = entities.erase(it);
		}

	}
}