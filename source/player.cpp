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
	x += velx*dt;
	y += vely*dt;

	velx = vely = 0;
}

void Player::moveUp()
{
	vely -= 100.0;
}

void Player::moveDown()
{
	vely += 100.0;
}

void Player::moveLeft()
{
	velx -= 100.0;
}

void Player::moveRight()
{
	velx += 100.0;
}

