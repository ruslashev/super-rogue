#include "player.hpp"

Player::Player()
{
	x = 10;
	y = 0;
	health = 100;
	type = ENT_PLAYER;
}

void Player::Update(double dt, double time)
{
	y += 100.0*dt;
	printf("%d\n", y);
}

