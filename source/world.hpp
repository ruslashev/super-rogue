#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include "entity.hpp"

class World
{
public:
	std::vector<std::unique_ptr<Entity>> entities;
	Entity *player;

	void PushEntity(Entity *ent);
};

#endif

