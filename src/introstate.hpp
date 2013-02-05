#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "gameengine.hpp"

class IntroState : public GameState
{
public:
	bool Init(GameEngine* game);
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

	glm::mat4 model, view, projection;
	GLuint vertexShader, fragmentShader, shaderProgram;
	GLint posAttrib, mvpUniform;

	GLuint testVbo;
	vector<glm::vec3> vertices;
};

#endif
