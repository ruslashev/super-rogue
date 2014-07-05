#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "entity.hpp"

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer
{
	SDL_Window *window;
	std::vector<Entity> entities;
public:
	SDL_Renderer *rend;

	void Create();
	void Draw(double marginToNextFrame);
	void PushEntity(Entity *ent);
	~Renderer();
};

#endif

