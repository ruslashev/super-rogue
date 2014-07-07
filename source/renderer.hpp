#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "utils.hpp"
#include "entity.hpp"
#include "world.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer
{
	SDL_Window *window;
public:
	SDL_Renderer *rend;
	SDL_Texture *entityTextures[3];

	void Create();
	void Draw(World *world);

	~Renderer();
};

#endif

