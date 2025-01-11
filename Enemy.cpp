#include "Enemy.h"

Enemy::Enemy(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H, std::string qn, int ID) : Entity(image, Name, X, Y, W, H)
{
	id = ID;
	currentFrame = 0.0f;

	obj = lvl.getObjectsByName("solid");

	if (name == "EasyEnemy")
	{
		sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(w), static_cast<int>(h)));
		dx = 0.1f;

		if (currentFrame > 5) currentFrame -= 4;
		sprite.setTextureRect(sf::IntRect(((76 * (int)currentFrame)), 0, -78, 75));
	}

}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
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

void Enemy::update(float time)
{
	currentFrame += 0.005f * time;
	if (currentFrame >= 4) currentFrame -= 3;
	sprite.setTextureRect(sf::IntRect(((78 * (int)currentFrame)), 0, -78, 75));

	x += dx * time;
	checkCollisionWithMap(dx, 0);
	sprite.setPosition(x + w / 2, y + h / 2);

	if (health <= 0) { life = false; death(time); }
}

void Enemy::death(float time)
{
	sprite.setColor(sf::Color::Red);
	deathAnimationTimer += time;
	if (deathAnimationTimer > 100)
	{
		isAnimationDeathEnd = true;
	}
}