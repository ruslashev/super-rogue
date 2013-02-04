#include "gameengine.hpp"

#include "introstate.hpp"
#include "playstate.hpp"

IntroState IntroState::m_IntroState;

bool IntroState::Init()
{


	return true;
}

void IntroState::Update(GameEngine* game)
{
/*	if (game->KeyPressed[GLFW_KEY_ESC]) {
		game->Quit();
	}
	if (game->KeyPressed(GLFW_KEY_SPACE)) {
		game->ChangeState(PlayState::Instance());
	}*/
}

void IntroState::Draw(GameEngine* game)
{

}

void IntroState::Cleanup()
{
	
}

void IntroState::Pause()
{

}

void IntroState::Resume()
{
	
}
