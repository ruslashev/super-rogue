#include "renderer.hpp"
#include "utils.hpp"
#include "player.hpp"
#include "world.hpp"
#include "input.hpp"

#include <fstream>

int main()
{
	World world;
	Renderer renderer;

	Player player;
	world.player = &player;
	world.PushEntity(new Entity);
	InputHandler inputHandler;

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
	double time = 0.0;
	const double dt = 0.01;

	double currentTime = SDL_GetTicks() / 1000.0;
	double accumulator = 0.0;

	while (!done)
	{
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				done = true;
			else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
				inputHandler.HandleInput(event.key, &world);
		}

		const double newTime = SDL_GetTicks() / 1000.0;
		const double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= dt) {
			world.Update(dt, time);
			accumulator -= dt;
			time += dt;
		}

		renderer.Draw(&world);
	}

	return 0;
}

