#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "gameengine.hpp"

class IntroState : public GameState
{
public:
	bool Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static IntroState* Instance() {
		return &m_IntroState;
	}

protected:
	IntroState() { }

private:
	static IntroState m_IntroState;


};

#endif
