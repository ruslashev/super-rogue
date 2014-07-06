#include "renderer.hpp"

Renderer::Renderer(World *nworld)
{
	world = nworld;
}

void Renderer::Create()
{
	int SDLInitCode = SDL_Init(SDL_INIT_VIDEO);
	assertf(SDLInitCode >= 0, "Failed to initialize SDL: %s", SDL_GetError());

	window = SDL_CreateWindow("Super Rogue",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 450,
			0);
	assertf(window != NULL, "Failed to create window: %s", SDL_GetError());

	rend = SDL_CreateRenderer(window, -1, 0);
	assertf(rend != NULL, "Failed to create renderer: %s", SDL_GetError());

	SDL_SetRenderDrawColor(rend, 20, 20, 20, 255);

	IMG_Init(IMG_INIT_PNG);
}

void Renderer::Draw()
{
	SDL_Rect placerRect;
	placerRect.w = placerRect.h = 50;
	SDL_RenderClear(rend);

	// Draw player
	placerRect.x = world->player->x;
	placerRect.y = world->player->y;
	SDL_RenderCopy(rend, entityTextures[ENT_PLAYER], NULL, &placerRect);

	// Draw rest of entities
	for (std::unique_ptr<Entity> &e : world->entities) {
		placerRect.x = e->x;
		placerRect.y = e->y;
		SDL_RenderCopy(rend, entityTextures[e->type], NULL, &placerRect);
	}

	SDL_RenderPresent(rend);
}

Renderer::~Renderer()
{
	IMG_Quit();
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

