#include "Bullet.h"

Bullet::Bullet(sf::Image& image, sf::String Name, TileMap& lvl, float X, float Y, float W, float H, sf::Vector2f direction) : Entity(image, Name, X, Y, W, H)
{

	obj = lvl.getAllObjects();
	direct = direction;


	distance = 0.0f;

	temp_vec_dir.x = direct.x - x;
	temp_vec_dir.y = direct.y - y;

	vector_direction_length = sqrt((temp_vec_dir.x * temp_vec_dir.x) + (temp_vec_dir.y * temp_vec_dir.y));
	normal_vec_x = temp_vec_dir.x / vector_direction_length;
	normal_vec_y = temp_vec_dir.y / vector_direction_length;
}

sf::Sprite& Bullet::getExMark()
{
	sf::Sprite sp;

	return sp;
}

void Bullet::update(float time)
{
	if (name == "Bullet")
	{

		//distance = sqrt((direct.x - x) * (direct.x - x) + (direct.y - y) * (direct.y - y)); for RPG game

		x += normal_vec_x * time;
		y += normal_vec_y * time;

		if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++)
		{

			if (getRect().intersects(obj[i].rect) && obj[i].name == "solid")
			{
				life = false;
				isAnimationDeathEnd = true;

			}

		}

		sprite.setPosition(x + w / 2, y + h / 2);
	}
}