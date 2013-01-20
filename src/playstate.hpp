#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gameengine.hpp"

class PlayState : public GameState
{
public:
	bool Init();
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
	
	SDL_Rect tiles[5];
	SDL_Surface* tilemap;
};

#endif
