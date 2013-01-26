#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

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

	vector<Entity*> m_Entities;

	Entity knight;
	
	SDL_Rect tiles[5];
	SDL_Surface* tilemap;

	static const unsigned char gamemap[10][10];
};

#endif
