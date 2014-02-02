#include "utils.hpp"

#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{
	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;
	try {
		const int initCode = SDL_Init(SDL_INIT_VIDEO);
		assertf(initCode >= 0, "Failed to initialize SDL: %s", SDL_GetError());

		sdlWindow = SDL_CreateWindow(
				"Super-rogue",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				800, 450,
				0
				);
		assertf(sdlWindow != NULL, "Failed to create window: %s", SDL_GetError());

		sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
		assertf(sdlRenderer != NULL, "Failed to create renderer: %s", SDL_GetError());

		IMG_Init(IMG_INIT_PNG);
	} catch (std::exception &e) {
		fprintf(stderr, "\x1b[31m" "ERROR" "\x1b[0m" " %s\n", e.what());
		return 1;
	}

	SDL_Surface *playerSurf = IMG_Load("protagonist.png");
	assertf(playerSurf != NULL, "Failed to load image: %s", IMG_GetError());
	SDL_Texture *playerTexture = SDL_CreateTextureFromSurface(sdlRenderer, playerSurf);
	assertf(playerTexture != NULL, "Failed to create player's texture: %s", SDL_GetError());
	SDL_FreeSurface(playerSurf);

	SDL_SetRenderDrawColor(sdlRenderer, 100, 100, 100, 255);

	SDL_Event sdlEvent;
	bool done = false;
	unsigned int prev = SDL_GetTicks();
	unsigned int lag = 0;
	const int MS_PER_UPDATE = 16;
	while (!done) {
		while (SDL_PollEvent(&sdlEvent) != 0) {
			if (sdlEvent.type == SDL_QUIT)
				done = true;
		}

		unsigned int curr = SDL_GetTicks();
		unsigned int elapsed = curr - prev;
		prev = curr;
		lag += elapsed;

		// processInput()

		while (lag >= MS_PER_UPDATE) {
			// update()
			lag -= MS_PER_UPDATE;
		}

		// render(lag/MS_PER_UPDATE)
		SDL_RenderClear(sdlRenderer);
		SDL_RenderCopy(sdlRenderer, playerTexture, NULL, NULL);
		SDL_RenderPresent(sdlRenderer);
	}

	IMG_Quit();
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	return 0;
}
