#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity
{
public:
	Player();
	void Update(double dt, double time);
};

#endif

