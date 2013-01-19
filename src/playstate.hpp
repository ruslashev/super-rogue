#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "gameengine.hpp"

class PlayState : public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static PlayState* Instance() {
		return &m_PlayState;
	}

protected:
	PlayState() { }

private:
	static PlayState m_PlayState;

	TTF_Font* font;
	SDL_Surface* textSurface;
};

#endif
