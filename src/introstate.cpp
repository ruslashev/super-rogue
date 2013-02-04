#include "gameengine.hpp"

#include "introstate.hpp"
#include "playstate.hpp"

IntroState IntroState::m_IntroState;

bool IntroState::Init(GameEngine* game)
{
	if (!LoadShader(GL_VERTEX_SHADER, vertexShader, "shaders/vertex.vs") || !LoadShader(GL_FRAGMENT_SHADER, fragmentShader, "shaders/fragment.fs")) {
		fprintf(stderr, "Failed to load shaders\n");
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	GLint successfulLink = GL_FALSE;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successfulLink);
	if (!successfulLink) { std::cerr << "Failed to link shader programn" << std::endl; exit(1); }
	glUseProgram(shaderProgram);
	posAttrib = glGetAttribLocation(shaderProgram, "vposition");

	projection = glm::ortho(0.f, (float)game->windowWidth, (float)game->windowHeight, 0.f);
	mvpUniform = glGetUniformLocation(shaderProgram, "mvp");

	return true;
}

void IntroState::Update(GameEngine* game)
{
	/*if (game->KeyPressed(GLFW_KEY_SPACE)) {
		game->ChangeState(PlayState::Instance());
	}*/

	if (glfwGetKey(GLFW_KEY_ESC) || ((glfwGetKey(GLFW_KEY_LCTRL) || glfwGetKey(GLFW_KEY_RCTRL)) && (glfwGetKey('C') || glfwGetKey('W') || glfwGetKey('D'))))
		game->Quit();
}

void IntroState::Draw(GameEngine* game)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers();
}

void IntroState::Cleanup()
{
	glDetachShader(shaderProgram, vertexShader);	
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void IntroState::Pause()
{

}

void IntroState::Resume()
{
	
}
