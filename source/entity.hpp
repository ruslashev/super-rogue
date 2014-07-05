#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
	SDL_Texture *texture;

	void LoadImage(SDL_Renderer *sdlRenderer, const char *path);
	virtual void Draw(SDL_Renderer *sdlRenderer) = 0;
};

#endif

