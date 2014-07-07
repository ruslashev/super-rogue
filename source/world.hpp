#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include "entity.hpp"
#include "player.hpp"

class World
{
public:
	std::vector<std::unique_ptr<Entity>> entities;
	Player *player;

	void PushEntity(Entity *ent);
	void Update(double dt, double time);
};

#endif

