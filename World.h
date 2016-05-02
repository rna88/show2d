#ifndef WORLD_H
#define WORLD_H


// componente (put these under namespace show/s2d)


namespace s2d
{

	struct entityInfo

class World
{
public:

	World();

	~World();

	World::addEntity(entityInfo& inputEntity);

	World::removeEntity(int index);

	World::update();


private:

	collisionGrid grid;

	std::vector<statistics> statisticsComponents;
	std::vector<behaviour> behaviourComponents;
	std::vector<action> actionComponents;
	std::vector<collision> collisionComponents;
	std::vector<physics> physicsComponents;
	std::vector<animation> animationComponents;
	std::vector<graphics> graphicsComponents;
	std::vector<sound> soundComponents;

};

}

#endif /* WORLD_H */
