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

	Projection = glm::perspective(45.f, (float)game->windowWidth/(float)game->windowHeight, 1.f, 100.f);
	mvpUniform = glGetUniformLocation(shaderProgram, "mvp");

	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			// byte tile = gamemap[x][y];

			int tileSize = 1;
			testEnt.vertices.push_back(glm::vec3(x*tileSize			, 0, y*tileSize			));
			testEnt.vertices.push_back(glm::vec3(x*tileSize			, 0, y*tileSize+tileSize));
			testEnt.vertices.push_back(glm::vec3(x*tileSize+tileSize, 0, y*tileSize			));
			testEnt.vertices.push_back(glm::vec3(x*tileSize+tileSize, 0, y*tileSize			));
			testEnt.vertices.push_back(glm::vec3(x*tileSize+tileSize, 0, y*tileSize+tileSize));
			testEnt.vertices.push_back(glm::vec3(x*tileSize			, 0, y*tileSize+tileSize));
		}

	testEnt.Upload();

	testEnt.SetPosition(glm::vec3(0, 0, 0));

	testPlayer.SetPosition(glm::vec3(0, 0, 5));

	return true;
}

void PlayState::Update(GameEngine* game)
{
	glm::vec3 oldPos = testPlayer.GetPosition();
	if (glfwGetKey('W'))
		oldPos.z -= 10*game->dt;

	if (glfwGetKey('S'))
		oldPos.z += 10*game->dt;

	if (glfwGetKey('A'))
		oldPos.x -= 10*game->dt;

	if (glfwGetKey('D'))
		oldPos.x += 10*game->dt;

	testPlayer.SetPosition(oldPos);

	mouseHelper.Update(game->windowWidth, game->windowHeight);

	testPlayer.rotation[0] = testPlayer.rotation[0] + mouseHelper.DeltaX;
	testPlayer.rotation[1] = min(max(testPlayer.rotation[1] + mouseHelper.DeltaY, -90.f), 90.f);

	View = glm::rotate(
		glm::rotate(
			glm::translate(
				glm::mat4(1),
				testPlayer.GetPosition()
			),
			testPlayer.rotation[1],
			glm::vec3(1.0f, 0.0f, 0.0f)
		),
		testPlayer.rotation[0],
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	glm::mat4 mvp = Projection * View;
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));


	if (glfwGetKey(GLFW_KEY_ESC) || ((glfwGetKey(GLFW_KEY_LCTRL) || glfwGetKey(GLFW_KEY_RCTRL)) && (glfwGetKey('C') || glfwGetKey('W') || glfwGetKey('D'))))
		game->Quit();
}

void PlayState::Draw(GameEngine* game)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	testEnt.Draw();

	glDisableVertexAttribArray(posAttrib);

	glfwSwapBuffers();
}

void PlayState::Cleanup()
{
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
