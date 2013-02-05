#include "gameengine.hpp"

bool GameEngine::Init(const char* title, int width, int height)
{
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);

	windowWidth = width;
	windowHeight = height;
	if (!glfwOpenWindow(width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
		fprintf(stderr, "Failed to open window\n");
		return false;
	}
	glfwSetWindowTitle(title);
	GLFWvidmode videoMode;
	glfwGetDesktopMode(&videoMode);
	glfwSetWindowPos(videoMode.Width/2 - width/2, videoMode.Height/2 - height/2);
	glfwSwapInterval(1);
	
	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {
		fprintf(stderr, "GLEW failed to initialize: %s\n", glewGetErrorString(glewInitStatus));
		return false;
	}
	
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glPointSize(5.0f);

	m_running = true;
	
	return true;
}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	glfwCloseWindow();
	glfwTerminate();
}

void GameEngine::ChangeState(GameState* state) 
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	if (!states.back()->Init(this))
	{
		PopState();
	}
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}
	
	// store and init the new state
	states.push_back(state);
	if (!states.back()->Init(this))
	{
		PopState();
	}
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}
	
	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	} else {
		Cleanup();
	}
}

void GameEngine::HandleEvents() 
{
	if (!glfwGetWindowParam(GLFW_OPENED))
	{
		m_running = false;
	}
}

void GameEngine::Update() 
{
	states.back()->Update(this);
}

void GameEngine::Draw() 
{
	states.back()->Draw(this);
}
