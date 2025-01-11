#ifndef _NPC_H_
#define _NPC_H_

#include <SFML/Graphics.hpp>

#include "level.h"
#include "Entity.h"
#include "Mission.h"
#include "Quest.h"

class NPC : public Entity
{
public:
	float currentFrame{ 0.0f };
	std::string questName;
	sf::Texture* exMarkTexture;
	sf::Sprite* exMarkSprite;
	Quest quest;

	NPC(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, int W, int H, std::string qn, int ID, Mission* missions);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time) override;
	sf::Sprite& getExMark() { return *exMarkSprite; }
	Quest getQuest() { return quest; }
};

#endif
