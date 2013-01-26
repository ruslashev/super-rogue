#include "main.hpp"

#include "gameengine.hpp"
#include "introstate.hpp"

int main(int argc, char *argv[])
{
	GameEngine game;
	
	if (!game.Init("pew pew pew"))
		return 0;
	
	game.ChangeState(IntroState::Instance());
	

	const double constDT = 0.01;
	double currentTime = SDL_GetTicks();

	while (game.Running())
	{
		double newTime = SDL_GetTicks();
		game.dt += min(newTime-currentTime, 0.25);
		currentTime = newTime;

		game.HandleEvents();

		while (game.dt >= constDT)
		{
			game.Update();
			game.time += constDT;
			game.dt -= constDT;
		}

		game.Draw();
	}
	
	game.Cleanup();

	return 0;
}
