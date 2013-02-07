#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameengine.hpp"

class PlayState : public GameState
{
public:
	bool Init(GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static PlayState* Instance() {
		return &m_PlayState;
	}

protected:
	PlayState() { }

private:
	static PlayState m_PlayState;

	static const unsigned char gamemap[10][10];

	glm::mat4 Model, View, Projection;
	GLuint vertexShader, fragmentShader, shaderProgram;
	GLint posAttrib, mvpUniform;

	Entity testEnt;
	Player testPlayer;
	MouseHelper mouseHelper;
};

#endif
