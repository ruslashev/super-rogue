#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>

using namespace std;

class GameState;

class GameEngine
{
public:
	void Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);
	void Cleanup();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	SDL_Surface* screen;

private:
	vector<GameState*> states;

	bool m_running;
	bool m_fullscreen;
};

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine* game) = 0;
	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	void ChangeState(GameEngine* game, GameState* state) {
		game->ChangeState(state);
	}

protected:
	GameState() { }
};

#endif
