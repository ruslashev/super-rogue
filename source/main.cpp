#include "renderer.hpp"
#include "player.hpp"
#include "utils.hpp"

#include <fstream>

int main()
{
	Renderer renderer;
	Player hero;
	try {
		renderer.Create();
		hero.LoadImage(renderer.sdlRenderer, "protagonist.png");
	} catch (std::exception &e) {
		fprintf(stderr, "\x1b[31m" "ERROR" "\x1b[0m" " %s\n", e.what());
		return 1;
	}

	renderer.PushEntity(hero);

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

		renderer.Redraw(lag/MS_PER_UPDATE);
	}

	return 0;
}
