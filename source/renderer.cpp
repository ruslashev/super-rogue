#include "utils.hpp"
#include "renderer.hpp"

void Renderer::Create()
{
	const int initCode = SDL_Init(SDL_INIT_VIDEO);
	assertf(initCode >= 0, "Failed to initialize SDL: %s", SDL_GetError());

	sdlWindow = SDL_CreateWindow(
			"Super rogue",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 450,
			0);
	assertf(sdlWindow != NULL, "Failed to create window: %s", SDL_GetError());

	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	assertf(sdlRenderer != NULL, "Failed to create renderer: %s", SDL_GetError());

	IMG_Init(IMG_INIT_PNG);
}

void Renderer::Redraw(double marginToNextFrame)
{
	for (std::vector<Player>::iterator i = entities.begin(); i != entities.end();
			i++) {
		i->Draw(sdlRenderer);
	}
}

void Renderer::PushEntity(Player &ent)
{
	entities.push_back(ent);
}

Renderer::~Renderer()
{
	IMG_Quit();
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

