#include "world.hpp"

void World::PushEntity(Entity *ent)
{
	entities.push_back(std::unique_ptr<Entity>(ent));
}

