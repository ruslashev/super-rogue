#include "gameengine.hpp"

#include "introstate.hpp"
#include "playstate.hpp"

IntroState IntroState::m_IntroState;

bool IntroState::Init(GameEngine* game)
{
	return true;
}

void IntroState::Update(GameEngine* game)
{
	//if (game->KeyPressed(GLFW_KEY_SPACE)) {
		game->ChangeState(PlayState::Instance());
	//}

	if (glfwGetKey(GLFW_KEY_ESC))
		game->Quit();
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
