#ifndef _COLLISION_ENTITY_H_
#define _COLLIDION_ENTITY_H_

#include "Entity.h"

class CollisionEntity
{
public:
	Entity* first;
	Entity* second;
	CollisionEntity(Entity* e1, Entity* e2) : first{ e1 }, second{ e2 } {}
	virtual ~CollisionEntity() {}
};
#endif