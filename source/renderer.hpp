#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "entity.hpp"

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer
{
	SDL_Window *sdlWindow;
	std::vector<Entity> entities;
public:
	SDL_Renderer *sdlRenderer;

	void Create();
	void Redraw(double marginToNextFrame);
	void PushEntity(const Entity &ent);
	~Renderer();
};

#endif

