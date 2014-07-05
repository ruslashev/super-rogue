#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

#include <SDL2/SDL.h>

class Entity
{
public:
	int x, y;
	SDL_Texture *texture;

	Entity() { texture = NULL; }

	void Draw(SDL_Renderer *rend) {
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, texture, NULL, NULL);
		SDL_RenderPresent(rend);
	}
};

#endif

