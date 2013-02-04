#include "gameengine.hpp"

#include "playstate.hpp"

PlayState PlayState::m_PlayState;

bool PlayState::Init()
{


	return true;
}

void PlayState::Update(GameEngine* game)
{
/*	if (game->KeyPressed(GLFW_KEY_SPACE)) {
		game->Quit();
	}*/
}

void PlayState::Draw(GameEngine* game)
{

}

void PlayState::Cleanup()
{
	
}

void PlayState::Pause()
{

}

void PlayState::Resume()
{
	
}
