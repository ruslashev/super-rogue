#include "gameengine.hpp"

bool GameEngine::Init(const char* title, int width, int height, int bpp)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	SDL_WM_SetCaption(title, title);

	if (!(screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE))) {
		fprintf(stderr, "Failed to set video mode: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		fprintf(stderr, "Failed to initialize TTF library: %s\n", TTF_GetError());
		return false;
	}

	for (int i = 0; i < 322; i++) {
		Keys[i] = false;
	}
	SDL_EnableKeyRepeat(0,0);

	dt = 0.0;
	time = 0.0;

	m_running = true;
	
	return true;
}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

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
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				Keys[event.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				Keys[event.key.keysym.sym] = false;
				break;

			case SDL_QUIT:
				Quit();
				break;
		}
	}
}

void GameEngine::Update() 
{
	states.back()->Update(this);
}

void GameEngine::Draw() 
{
	states.back()->Draw(this);
}
