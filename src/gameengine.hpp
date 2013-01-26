#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "utils.hpp"
#include "entity.hpp"

class GameState;

class GameEngine
{
public:
	bool Init(const char* title, int width=800, int height=600, int bpp=32);
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
	virtual bool Init() = 0;
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
