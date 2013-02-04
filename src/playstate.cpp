#include "gameengine.hpp"

#include "playstate.hpp"

PlayState PlayState::m_PlayState;

bool PlayState::Init(GameEngine* game)
{
	return true;
}

void PlayState::Update(GameEngine* game)
{
	if (glfwGetKey(GLFW_KEY_ESC) || ((glfwGetKey(GLFW_KEY_LCTRL) || glfwGetKey(GLFW_KEY_RCTRL)) && (glfwGetKey('C') || glfwGetKey('W') || glfwGetKey('D'))))
		game->Quit();
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
