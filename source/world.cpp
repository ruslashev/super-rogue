#include "world.hpp"

void World::PushEntity(Entity *ent)
{
	entities.push_back(std::unique_ptr<Entity>(ent));
}

void World::Update(double dt, double time)
{
	player->Update(dt, time);
	for (std::unique_ptr<Entity> &e : entities) {
		e->Update(dt, time);
	}
}

