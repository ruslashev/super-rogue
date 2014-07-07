#include "input.hpp"

void handleInput(SDL_KeyboardEvent key, World *world)
{
	if (key.keysym.sym == SDLK_w) world->player->moveUp();
	if (key.keysym.sym == SDLK_s) world->player->moveDown();
	if (key.keysym.sym == SDLK_a) world->player->moveLeft();
	if (key.keysym.sym == SDLK_d) world->player->moveRight();
}

