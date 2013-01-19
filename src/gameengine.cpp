#include "gameengine.hpp"

void GameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetCaption(title, title);

	screen = SDL_SetVideoMode(width, height, bpp, 0);

	//TODO: screen == NULL

	TTF_Init();

	//TODO: TTF_Init == -1

	m_running = true;
	
	printf("GameEngine Init\n");
}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

	printf("GameEngine Cleanup\n");

	TTF_Quit();
	
	SDL_Quit();
}

void GameEngine::ChangeState(GameState* state) 
{
	// cleanup the current state
	if (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty())
	{
		states.back()->Pause();
	}
	
	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}
	
	// resume previous state
	if (!states.empty())
	{
		states.back()->Resume();
	}
}

void GameEngine::HandleEvents() 
{
	states.back()->HandleEvents(this);
}

void GameEngine::Update() 
{
	states.back()->Update(this);
}

void GameEngine::Draw() 
{
	states.back()->Draw(this);
}
