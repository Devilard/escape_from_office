#ifndef _ENTITY_HANDLER_H_
#define _ENTITY_HANDLER_H_

#include <vector>

#include "Entity.h"



class EntityHandler
{
public:
	std::vector<Entity*> entities;
	EntityHandler() {}
	void addEntity(Entity* e);
	
	void update(float time);
	//std::vector<Entity*> checkCollisionForEntity();
	Entity* getEntityById(int id);
	std::vector<Entity*> getAllNpc();

};
#endif

