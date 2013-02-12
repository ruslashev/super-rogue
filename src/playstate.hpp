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

	glm::mat4 ModelMat, ViewMat, ProjectionMat;
	GLuint vertexShader, fragmentShader, shaderProgram;
	GLint posAttrib, mvpUniformAttrib, timeUniformAttrib;

	forward_list<Drawable> boxes;
	Player testPlayer;
};

#endif
