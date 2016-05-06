#ifndef WORLD_H
#define WORLD_H

#include <iostream>

// System headers
#include "physicsSystem.h"
#include "graphicsSystem.h"

#include "Component.h"

namespace s2d
{


class World
{
public:
	
	World()
	{

	}

	~World()
	{

	}

	World::addEntity(entityInfo& inputEntity)
	{

	}

	World::removeEntity(int index)
	{

	}

	World::update()
	{

	}


private:
	
	std::vector<physicsComponent> physicsComponentList;	
	std::vector<graphicsComponent> graphicsComponentList;	

};

}

#endif /* WORLD_H */
