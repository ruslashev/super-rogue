#include "gameengine.hpp"

bool GameEngine::Init(const char* title, int width, int height)
{


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

	// glfwCloseWindow();
	// glfwTerminate();
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
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}
	
	// store and init the new state
	states.push_back(state);
	states.back()->Init();
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
	}
}

void GameEngine::HandleEvents() 
{

}

void GameEngine::Update() 
{
	states.back()->Update(this);
}

void GameEngine::Draw() 
{
	states.back()->Draw(this);
}

bool GameEngine::LoadShader(GLenum type, GLuint& shader, std::string filename)
{
	std::ifstream fileStream (filename.c_str());
	if (!fileStream.good()) {
		fprintf(stderr, "Failed to open shader \"%s\"\n", filename.c_str());
		return false;
	}

	std::string str;
	fileStream.seekg(0, std::ios::end);
	str.resize(fileStream.tellg());
	fileStream.seekg(0, std::ios::beg);
	fileStream.read(&str[0], str.size());
	fileStream.close();

	const char* source = str.c_str();
	
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	
	GLint compileSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE) {		
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char compileLog[infoLogLength+1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, compileLog);
		fprintf(strerr, "Shader \"%s\" failed to compile. Error log:\n%s", filename.c_str(), compileLog);
		glDeleteShader(shader);
		return false;
	}

	return true;
}