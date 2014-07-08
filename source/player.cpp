#include "player.hpp"
#include "utils.hpp"

Player::Player()
{
	x = 100;
	y = 100;
	oldx = x;
	oldy = y;
	health = 100;
	type = ENT_PLAYER;
}

void Player::Update(double dt, double time)
{
	const double tempx = x, tempy = y;

	const double speedLimit = 5.0;
	const double slowdown = 0.5;

	x += clamp((x - oldx + accelx * dt*dt), -speedLimit, speedLimit);
	y += clamp((y - oldy + accely * dt*dt), -speedLimit, speedLimit);

	if (!(int)accelx)
		oldx = lerp(tempx, x, slowdown);
	else
		oldx = tempx;

	if (!(int)accely)
		oldy = lerp(tempy, y, slowdown);
	else
		oldy = tempy;
}

void Player::moveUp()    { accely -= 10000; }
void Player::moveDown()  { accely += 10000; }
void Player::moveLeft()  { accelx -= 10000; }
void Player::moveRight() { accelx += 10000; }

void Player::resetUp()    { accely = 0; }
void Player::resetDown()  { accely = 0; }
void Player::resetLeft()  { accelx = 0; }
void Player::resetRight() { accelx = 0; }

