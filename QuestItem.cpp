#include "QuestItem.h"


QuestItem::QuestItem(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H) : Entity(image, Name, X, Y, W, H)
{
	currentFrame = 0.0f;
	questName = "FuckingMouse";
	obj = lvl.getAllObjects();
	sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(16), static_cast<int>(16)));
}

void QuestItem::update(float time)
{
	sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(16), static_cast<int>(16)));
	sprite.setPosition(x + w / 2, y + h / 2);
}