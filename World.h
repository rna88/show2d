#ifndef WORLD_H
#define WORLD_H


// System headers


namespace s2d
{


class World
{
public:

	World();

	~World();

	World::addEntity(entityInfo& inputEntity);

	World::removeEntity(int index);

	World::update();


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
