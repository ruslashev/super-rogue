#include "gameengine.hpp"

#include "introstate.hpp"

int main(int argc, char *argv[])
{
	GameEngine game;

	game.Init("pew pew pew");

	game.ChangeState(IntroState::Instance());

	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	game.Cleanup();

	return 0;
}
