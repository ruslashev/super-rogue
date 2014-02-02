#include <fstream>
#include <SDL2/SDL.h>
#include <stdexcept>

void assertf(bool condition, const char *format, ...)
{
#ifndef RELEASE
	if (!condition) {
		char output[512];
		va_list args;
		va_start(args, format);
		vsnprintf(output, 512, format, args);
		va_end(args);
		std::string outputStr = output;
		outputStr += '\n';
		throw std::runtime_error(outputStr);
	}
#endif
}

int main()
{
	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;
	try {
		const int initCode = SDL_Init(SDL_INIT_VIDEO);
		assertf(initCode >= 0, "Failed to initialize SDL");

		sdlWindow = SDL_CreateWindow(
				"Super-rogue",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				800, 450,
				0
				);
		assertf(sdlWindow != NULL, "Failed to create window");

		sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
		assertf(sdlRenderer != NULL, "Failed to create renderer");
	} catch (std::exception &e) {
		fprintf(stderr, "\x1b[31m" "ERROR" "\x1b[0m" " %s\n", e.what());
		return 1;
	}

	SDL_SetRenderDrawColor(sdlRenderer, 100, 100, 100, 255);

	SDL_Event sdlEvent;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&sdlEvent) != 0) {
			if (sdlEvent.type == SDL_QUIT)
				done = true;
		}

		SDL_RenderClear(sdlRenderer);
		SDL_RenderPresent(sdlRenderer);
	}

	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	return 0;
}
