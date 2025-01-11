#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "math.h"
class Bullet : public Entity
{
public:
	sf::Vector2f direct;
	sf::Vector2f char_vector;
	float vector_direction_length{ 0.0f };
	float distance{ 0.0f };
	float normal_vec_x;
	float normal_vec_y;
	sf::Vector2f temp_vec_dir;

	Bullet(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H, sf::Vector2f direction);

	sf::Sprite& getExMark();

	void update(float time);
};

#endif
