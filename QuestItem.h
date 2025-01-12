#ifndef _QUEST_ITEM_H_
#define _QUEST_ITEM_H_

#include <string>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "level.h"

class QuestItem : public Entity
{
public:
	std::string questName;
	float currentFrame;
	QuestItem(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H);

	void update(float time) override;

};

#endif

