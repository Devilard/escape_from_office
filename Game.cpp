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
	entityHandler = new EntityHandler();
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

	for (auto u = users.begin(); u != users.end(); ++u)
	{
		if (u->GetPropertyString("QuestName") != "")
		{
			 if (dynamic_cast<NPC*>(entityHandler->getEntityById(u->id)) != nullptr)
			 {
				 std::cout << u->GetPropertyString("QuestName")  << "\n";
				 std::cout << entityHandler->getEntityById(u->id) << "\n";
				 std::cout << dynamic_cast<NPC*>(entityHandler->getEntityById(u->id)) << "\n";

				 dynamic_cast<NPC*>(entityHandler->getEntityById(u->id))->addQuest(u->GetPropertyString("QuestName"));
			 }
		}
		
	}

	
	

}

void Game::fillEntitiesList()
{
	
	//Filling the enemy list
	for (int i = 0; i < enemies.size(); i++)
	{
		std::string questName = enemies[i].GetPropertyString("QuestName");
		if (questName != "")
		{
			entityHandler->addEntity(new Enemy(*easyEnemyImg, "EasyEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 78, 65, questName, enemies[i].id));
		}
		else
		{
			entityHandler->addEntity(new Enemy(*easyEnemyImg, "EasyEnemy", *currentLevel, enemies[i].rect.left, enemies[i].rect.top, 78, 65, questName, enemies[i].id));
		}

	}

	for (int i = 0; i < enemiesA.size(); i++)
	{
		std::string questName = "";
		entityHandler->addEntity(new Enemy(*angelEnemyImg, "EasyEnemy", *currentLevel, enemiesA[i].rect.left, enemiesA[i].rect.top, 78, 65, questName, enemiesA[i].id));
	}

	for (int i = 0; i < users.size(); i++)
	{
		std::string questName = users[i].GetPropertyString("QuestName");
		if (questName != "")
		{
			//std::cout << "string 142 Game.cpp: User id " << users[i].id << "\n";
			entityHandler->addEntity(new NPC(*userImg, "User", *currentLevel, users[i].rect.left,
				users[i].rect.top, 64, 64, questName, users[i].id, mission, questHandler));
		}
		else
		{
			entityHandler->addEntity(new NPC(*userImg, "User", *currentLevel, users[i].rect.left,
				users[i].rect.top, 64, 64, "", users[i].id, mission, questHandler));
		}

	}

	for (int i = 0; i < collectables.size(); i++)
	{
		entityHandler->addEntity(new QuestItem(*questItemImg, "questItem", *currentLevel, collectables[i].rect.left, collectables[i].rect.top, 16, 16));
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
		for (auto it = getPlayer().questList.begin(); it != getPlayer().questList.end(); ++it)
		{
			missionText->setString((*it) + "\n");
		}

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
					player->action(entityHandler, getGameView());
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
				if (getPlayer().state != stateObject::cant_move)
				{
					getPlayer().shoot(entityHandler, pos, bulletImg, currentLevel);
				}

				if (getPlayer().state == stateObject::cant_move)
				{
					
					getPlayer().questDialog->chooseQuest(window);
				}
			}
		}


	}
}

void Game::render(sf::RenderWindow& window, std::list<Entity*>::iterator& it)
{
	window.clear();
	window.draw(getCurrentLevel());
	for (auto it = entityHandler->entities.begin(); it != entityHandler->entities.end(); it++)
	{
		if (dynamic_cast<NPC*>((*it)) != nullptr)
		{
			if (!dynamic_cast<NPC*>((*it))->questList.empty())
			{
				window.draw((*it)->getExMark());
			}
			window.draw((*it)->sprite);
		}
		else
		{
			window.draw((*it)->sprite);

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



	
	if(!getPlayer().questDialog->isShowQuestDialog) 
	{
		window.draw(*(getPlayer().questDialog->sprite));
		//window.draw(*(getPlayer().questDialog->text));
		for (std::vector<sf::Text*>::iterator it = getPlayer().questDialog->questList.begin(); it != getPlayer().questDialog->questList.end(); ++it)
		{
			window.draw(*(*it));
		}

		
		getPlayer().questDialog->update(getGameView());

	}
	

	window.display();
}

void Game::entitiesUpdate(float time)
{
	//entityHandler->update(time);


	for (auto it = entityHandler->entities.begin(); it != entityHandler->entities.end();)
	{
		Entity* b = *it;
		b->update(time);
		if (b->life == false && b->isAnimationDeathEnd == true)
		{
			it = entityHandler->entities.erase(it); delete b;
		}
		else { it++; }
	}

	for (auto it = entityHandler->entities.begin(); it != entityHandler->entities.end(); it++)
	{

		for (auto it2 = entityHandler->entities.begin(); it2 != entityHandler->entities.end(); it2++)
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

	for (auto it = entityHandler->entities.begin(); it != entityHandler->entities.end();)
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
				/*
				questHandler->getQuestByName();

				if (player->questList[qn].status == statuses::taken)
				{
					player->questList[qn].status = statuses::wait_execution;
					isCollect = true;
				}
				*/
			}

		}

		if (isCollect == false)
		{
			it++;
		}
		else
		{
			it = entityHandler->entities.erase(it);
		}

	}
}