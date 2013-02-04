#include "main.hpp"

#include "gameengine.hpp"
#include "introstate.hpp"

int main(int argc, char *argv[])
{
	GameEngine game;
	
	if (!game.Init("pew pew pew"))
		return 0;
	
	game.ChangeState(IntroState::Instance());
	
	// double currentTime = SDL_GetTicks();
	// double accumulator = 0.0;

	//game.dt = 1 / 60.f;
	//game.time = 0.0;
	
	while (game.Running())
	{
		// double newTime = SDL_GetTicks();
		// accumulator += min(newTime-currentTime, 0.25);
		// currentTime = newTime;

		// while (accumulator >= game.dt)
		// {
			game.Update();
			game.HandleEvents();
			//game.time += game.dt;
			// accumulator -= game.dt;
		// }

		// game.alpha = accumulator / game.dt;
		game.Draw();
	}
	
	game.Cleanup();

	return 0;
}
