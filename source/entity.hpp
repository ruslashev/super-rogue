#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

enum EntityType { ENT_DUMMY = 0, ENT_PLAYER, ENT_AI };
class Entity
{
public:
	int x, y;
	int health;
	EntityType type;

	Entity() : x(0), y(0), health(1), type(ENT_DUMMY) {};
	virtual void Update(double dt, double time) { x += 100*dt; };
};

#endif

