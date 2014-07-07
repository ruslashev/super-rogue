#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity
{
	double velx, vely;
public:
	Player();
	void Update(double dt, double time);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif

