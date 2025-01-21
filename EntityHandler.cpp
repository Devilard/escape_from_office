#include "EntityHandler.h"

void EntityHandler::addEntity(Entity* e)
{
	entities.push_back(e);
}



void EntityHandler::update(float time)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->update(time);
		
	}
}

//std::vector<Entity*> EntityHandler::checkCollisionForEntity()
//{
//	for (auto it = this->entities.begin(); it != this->entities.end(); ++it)
//	{
//		for (auto it2 = this->entities.begin(); it2 != this->entities.end(); ++it2)
//		{
//
//		}
//	}
//}

Entity* EntityHandler::getEntityById(int id)
{
	bool isFind = false;

	for (auto e = entities.begin(); e != entities.end(); ++e)
	{
		if ((*e)->id == id)
		{
			isFind = true;
			return *(e);
		}
			
	}
	if (isFind == false)
		return nullptr;
}