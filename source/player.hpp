#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity
{
	double oldx, oldy;
	double accelx, accely;
public:
	Player();
	void Update(double dt, double time);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void resetUp();
	void resetDown();
	void resetLeft();
	void resetRight();
};

#endif

