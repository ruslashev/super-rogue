#include "gameengine.hpp"

#include "playstate.hpp"

PlayState PlayState::m_PlayState;

const unsigned char PlayState::gamemap[10][10] = {
	{3,3,3,3,3,3,3,3,3,3},
	{3,0,0,0,0,2,2,0,0,3},
	{3,0,1,0,2,4,4,2,0,3},
	{3,1,1,1,0,2,2,4,2,3},
	{3,1,1,0,0,2,2,4,2,3},
	{3,0,0,0,2,3,3,3,4,3},
	{3,0,0,0,2,3,4,4,4,3},
	{3,0,0,0,2,3,3,3,4,3},
	{3,0,0,0,0,2,2,3,4,3},
	{3,3,3,3,3,3,3,3,3,3}
};

bool PlayState::Init(GameEngine* game)
{
	if (!LoadShader(GL_VERTEX_SHADER, vertexShader, "data/shaders/vertex.vs") || !LoadShader(GL_FRAGMENT_SHADER, fragmentShader, "data/shaders/fragment.fs")) {
		fprintf(stderr, "Failed to load shaders\n");
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	LinkShaderProgram(shaderProgram);
	glUseProgram(shaderProgram);
	posAttrib = glGetAttribLocation(shaderProgram, "vposition");

	projection = glm::perspective(60.f, (float)game->windowWidth/(float)game->windowHeight, 1.f, 100.f);
	mvpUniform = glGetUniformLocation(shaderProgram, "mvp");

	testEnt.vertices.push_back(glm::vec3(1.0, 0.0, 0.0));
	testEnt.vertices.push_back(glm::vec3(0.0, 1.0, 0.0));
	testEnt.vertices.push_back(glm::vec3(0.0, 0.0, 1.0));
	glGenBuffers(1, &testVbo);
	glBindBuffer(GL_ARRAY_BUFFER, testVbo);
	glBufferData(GL_ARRAY_BUFFER, testEnt.vertices.size()*sizeof(testEnt.vertices[0]), testEnt.vertices.data(), GL_STATIC_DRAW);

	return true;
}

void PlayState::Update(GameEngine* game)
{
	view = glm::lookAt(glm::vec3(0, 0, 5-glfwGetMouseWheel()), glm::vec3(0), glm::vec3(0, 1, 0));

	glm::mat4 mvp = projection * view * glm::mat4(1);
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));

	if (glfwGetKey(GLFW_KEY_ESC) || ((glfwGetKey(GLFW_KEY_LCTRL) || glfwGetKey(GLFW_KEY_RCTRL)) && (glfwGetKey('C') || glfwGetKey('W') || glfwGetKey('D'))))
		game->Quit();
}

void PlayState::Draw(GameEngine* game)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, testVbo);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, testEnt.vertices.size());

	glDisableVertexAttribArray(posAttrib);

	glfwSwapBuffers();
}

void PlayState::Cleanup()
{
	glDeleteBuffers(1, &testVbo);

	glDetachShader(shaderProgram, vertexShader);	
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void PlayState::Pause()
{

}

void PlayState::Resume()
{
	
}
