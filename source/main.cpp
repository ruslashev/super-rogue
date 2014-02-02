#include <fstream>
#include <SDL2/SDL.h>

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	// TODO check for NULLs
	SDL_Window *sdlWindow = SDL_CreateWindow(
		"Super-rogue",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		0, 0,
		SDL_WINDOW_FULLSCREEN_DESKTOP
	);

	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);

	// SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(sdlRenderer, 800, 450);

	SDL_SetRenderDrawColor(sdlRenderer, 100, 100, 100, 255);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderPresent(sdlRenderer);

	SDL_Delay(5000);

	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	return 0;
}
