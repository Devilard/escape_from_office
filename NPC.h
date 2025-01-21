#ifndef _NPC_H_
#define _NPC_H_

#include <SFML/Graphics.hpp>

#include "level.h"
#include "Entity.h"
#include "Mission.h"
#include "Quest.h"
#include "QuestHandler.h"

class NPC : public Entity
{
public:
	float currentFrame{ 0.0f };
	sf::Texture* exMarkTexture;
	sf::Sprite* exMarkSprite;

	std::vector<sf::String> questList;

	NPC(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, int W, int H,
		std::string qn, int ID, Mission* missions, QuestHandler* questHandelr);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time) override;
	sf::Sprite& getExMark() { return *exMarkSprite; }

	void addQuest(std::string questName);
};

#endif
