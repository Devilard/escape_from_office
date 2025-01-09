#ifndef _NPC_H_
#define _NPC_H_

#include <SFML/Graphics.hpp>

#include "level.h"
#include "Entity.h"

class NPC : public Entity
{
public:
	float currentFrame{ 0.0f };
	std::string questName;

	NPC(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, int W, int H, std::string qn, int ID) : Entity(image, Name, X, Y, W, H)
	{
		id = ID;
		questName = qn;
		if (questName != "")
		{
			isHaveQuest = true;
		}
		//setQuest("questName");
	}
};

#endif
