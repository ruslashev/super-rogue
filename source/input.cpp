#include "input.hpp"

void handleInput(SDL_KeyboardEvent key, World *world)
{
	if (key.keysym.sym == SDLK_w) {
		if (key.state == SDL_PRESSED)
			world->player->moveUp();
		else
			world->player->resetUp();
	}
	if (key.keysym.sym == SDLK_s) {
		if (key.state == SDL_PRESSED)
			world->player->moveDown();
		else
			world->player->resetDown();
	}
	if (key.keysym.sym == SDLK_a) {
		if (key.state == SDL_PRESSED)
			world->player->moveLeft();
		else
			world->player->resetLeft();
	}
	if (key.keysym.sym == SDLK_d) {
		if (key.state == SDL_PRESSED)
			world->player->moveRight();
		else
			world->player->resetRight();
	}
}

