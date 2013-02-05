#include "gameengine.hpp"

#include "introstate.hpp"
#include "playstate.hpp"

IntroState IntroState::m_IntroState;

bool IntroState::Init(GameEngine* game)
{
	if (!LoadShader(GL_VERTEX_SHADER, vertexShader, "data/shaders/vertex.vs") || !LoadShader(GL_FRAGMENT_SHADER, fragmentShader, "data/shaders/fragment.fs")) {
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

	projection = glm::perspective(60.f, (float)game->windowWidth/(float)game->windowHeight, 1.f, 100.f);
	mvpUniform = glGetUniformLocation(shaderProgram, "mvp");


	vertices.push_back(glm::vec3(1.0, 0.0, 0.0));
	vertices.push_back(glm::vec3(0.0, 1.0, 0.0));
	vertices.push_back(glm::vec3(0.0, 0.0, 1.0));
	glGenBuffers(1, &testVbo);
	glBindBuffer(GL_ARRAY_BUFFER, testVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

	return true;
}

void IntroState::Update(GameEngine* game)
{
	/*if (game->KeyPressed(GLFW_KEY_SPACE)) {
		game->ChangeState(PlayState::Instance());
	}*/

	view = glm::lookAt(glm::vec3(0, 0, 5-glfwGetMouseWheel()), glm::vec3(0), glm::vec3(0, 1, 0));

	glm::mat4 mvp = projection * view * glm::mat4(1);
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));

	if (glfwGetKey(GLFW_KEY_ESC) || ((glfwGetKey(GLFW_KEY_LCTRL) || glfwGetKey(GLFW_KEY_RCTRL)) && (glfwGetKey('C') || glfwGetKey('W') || glfwGetKey('D'))))
		game->Quit();
}

void IntroState::Draw(GameEngine* game)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, testVbo);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(posAttrib);

	glfwSwapBuffers();
}

void IntroState::Cleanup()
{
	glDeleteBuffers(1, &testVbo);

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
