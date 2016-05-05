#ifndef WORLD_H
#define WORLD_H

#include <iostream>

// System headers
//#include "statistics.h"
//#include "behaviour.h"
//#include "action.h"
//#include "collision.h"
#include "physicsSystem.h"
//#include "animation.h"
#include "graphicsSystem.h"
//#include "sound.h"

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
	
	//std::vector<statistics> statisticsComponents;	
	//std::vector<behaviour> behaviourComponents;
	//std::vector<action> actionComponents;	
	//std::vector<collision> collisionComponents;	
	std::vector<physicsComponent> physicsComponentList;	
	//std::vector<animation> animationComponents;	
	std::vector<graphicsComponent> graphicsComponentList;	
	//std::vector<sound> soundComponents;	

};

}

#endif /* WORLD_H */
