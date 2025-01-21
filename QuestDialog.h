#ifndef _QUEST_DIALOG_H_
#define _QUEST_DIALOG_H_

#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "NPC.h"
#include "GameView.h"

class QuestDialog
{
public:
	sf::Text* text;
	sf::Image* img;
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::Font* font;
	bool isShowQuestDialog;
	vector<sf::Text*> questList;
	

	QuestDialog() : text(nullptr), img(nullptr), texture(nullptr),
		sprite(nullptr), isShowQuestDialog(true), font(nullptr)
	{}

	~QuestDialog()
	{
		delete text;
		delete img;
		delete texture;
		delete sprite;
		delete font;
	}

	void init();

	void show(const NPC* npc, GameView* view);
	void high();
	void update(GameView* view);

	sf::String chooseQuest(sf::RenderWindow& window);
	
};

#endif