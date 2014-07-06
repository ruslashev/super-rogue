#include "renderer.hpp"
#include "utils.hpp"
#include "player.hpp"
#include "world.hpp"

#include <fstream>

int main()
{
	World world;
	Renderer renderer(&world);
	Player player;

	world.player = &player;

	try {
		renderer.Create();
		LoadImage(renderer.rend, "enemy.png",       &renderer.entityTextures[0]);
		LoadImage(renderer.rend, "protagonist.png", &renderer.entityTextures[1]);
		LoadImage(renderer.rend, "enemy.png",       &renderer.entityTextures[2]);
	} catch (std::exception &e) {
		fprintf(stderr, "\x1b[31m" "ERROR" "\x1b[0m" " %s\n", e.what());
		return 1;
	}

	SDL_Event event;
	bool done = false;
	unsigned int prev = SDL_GetTicks();
	unsigned int lag = 0;
	const int MS_PER_UPDATE = 16;
	while (!done) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
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

		renderer.Draw(lag/MS_PER_UPDATE);
	}

	return 0;
}

