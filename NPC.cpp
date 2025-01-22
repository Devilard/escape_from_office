#include "NPC.h"

NPC::NPC(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, int W, int H,
	std::string qn, int ID, QuestHandler* questHandelr)
	: Entity(image, Name, X, Y, W, H)
{

	exMarkTexture = new sf::Texture;
	exMarkTexture->loadFromFile("layouts/img/exclamation_mark.png");
	exMarkSprite = new sf::Sprite;
	exMarkSprite->setTexture(*exMarkTexture);
	exMarkSprite->setTextureRect(sf::IntRect(12, 0, 7, 28));
	sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(w), static_cast<int>(h)));

	obj = lvl.getObjectsByName("solid");

	currentFrame = 0.0f;
	id = ID;

}

void NPC::checkCollisionWithMap(float Dx, float Dy)
{

	for (int i = 0; i < obj.size(); i++)
	{
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1f; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1f; sprite.scale(-1, 1); }
			}
		}
	}
}

void NPC::update(float time)
{
	currentFrame += 0.005f * time;
	if (currentFrame >= 4) currentFrame -= 3;
	sprite.setTextureRect(sf::IntRect(((30 * (int)currentFrame)), 1, 30, 72));

	x += dx * time;
	checkCollisionWithMap(dx, 0);
	sprite.setPosition(x + w / 2, y + h / 2);
	exMarkSprite->setPosition(x + 15, y - 40);


}

void NPC::addQuest(std::string questName)
{
	if (questName != "")
	{
		questList.push_back(questName);
	}
}