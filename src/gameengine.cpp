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
	if (!glfwOpenWindow(width, height, 0, 0, 0, 0, 24, 8, GLFW_WINDOW)) {
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

	// loadShader(GL_VERTEX_SHADER, vertexShader, "shaders/vert.glsl");
	// loadShader(GL_FRAGMENT_SHADER, fragmentShader, "shaders/frag.glsl");
	// shaderProgram = glCreateProgram();
	// glAttachShader(shaderProgram, vertexShader);
	// glAttachShader(shaderProgram, fragmentShader);
	// glLinkProgram(shaderProgram);
	// GLint successfulLink = GL_FALSE;
	// glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successfulLink);
	// if (!successfulLink) { std::cerr << "Failed to link shader programn" << std::endl; exit(1); }
	// glUseProgram(shaderProgram);
	// posAttrib = glGetAttribLocation(shaderProgram, "vposition");

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

bool GameEngine::LoadShader(GLenum type, GLuint& shader, const char* filename)
{
	std::ifstream fileStream (filename);
	if (!fileStream.good()) {
		fprintf(stderr, "Failed to open shader \"%s\"\n", filename);
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
		fprintf(stderr, "Shader \"%s\" failed to compile. Error log:\n%s", filename, compileLog);
		glDeleteShader(shader);
		return false;
	}

	return true;
}