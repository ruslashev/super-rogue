#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "utils.hpp"
#include "entity.hpp"

class GameState;

class GameEngine
{
public:
	bool Init(const char* title, int width=800, int height=600);
	void Cleanup();
	
	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	bool LoadShader(GLenum type, GLuint& shader, const char* filename);

private:
	int windowWidth, windowHeight;
	vector<GameState*> states;

	bool m_running;
};

class GameState
{
public:
	virtual bool Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	void ChangeState(GameEngine* game, GameState* state) {
		game->ChangeState(state);
	}

protected:
	GameState() { }
};

#endif
