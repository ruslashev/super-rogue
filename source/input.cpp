#include "input.hpp"

InputHandler::InputHandler()
{
	button_w = &moveUp;
	button_s = &moveDown;
	button_a = &moveLeft;
	button_d = &moveRight;
}

Command *InputHandler::getCommand(SDL_KeyboardEvent key)
{
	if (key.state == SDL_PRESSED) {
		if (key.keysym.sym == SDLK_w) return button_w;
		if (key.keysym.sym == SDLK_s) return button_s;
		if (key.keysym.sym == SDLK_a) return button_a;
		if (key.keysym.sym == SDLK_d) return button_d;
	}
	return NULL;
}

void InputHandler::HandleInput(SDL_KeyboardEvent key, World *world)
{
	world->player->resetMoving();

	Command *comm = getCommand(key);
	if (comm)
		comm->execute(world->player);
}

