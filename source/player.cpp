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
	y += 20.0*dt;
}

