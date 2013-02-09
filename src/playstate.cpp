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

	ProjectionMat = perspective(60.f, (float)game->windowWidth/(float)game->windowHeight, 0.1f, 100.f);
	mvpUniformAttrib = glGetUniformLocation(shaderProgram, "mvp");
	timeUniformAttrib = glGetUniformLocation(shaderProgram, "time");

	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			// byte tile = gamemap[x][y];

			int tileSize = 1;
			testEnt.m_vertices.push_back(vec3(x*tileSize			, 0, y*tileSize			));
			testEnt.m_vertices.push_back(vec3(x*tileSize			, 0, y*tileSize+tileSize));
			testEnt.m_vertices.push_back(vec3(x*tileSize+tileSize	, 0, y*tileSize			));
			testEnt.m_vertices.push_back(vec3(x*tileSize+tileSize	, 0, y*tileSize			));
			testEnt.m_vertices.push_back(vec3(x*tileSize+tileSize	, 0, y*tileSize+tileSize));
			testEnt.m_vertices.push_back(vec3(x*tileSize			, 0, y*tileSize+tileSize));
		}

	testEnt.Upload();

	testEnt.SetPosition(vec3(0, 0, 0));

	testPlayer.SetPosition(vec3(0, 4, 0));

	return true;
}

void PlayState::Update(GameEngine* game)
{
	if (glfwGetKey('W'))
		testPlayer.Move(10*game->dt, vec3(1));
	if (glfwGetKey('S'))
		testPlayer.Move(-10*game->dt, vec3(1));

	int mouseDeltaX, mouseDeltaY;
	GetMouseDeltas(game->windowWidth, game->windowHeight, 1.f, mouseDeltaX, mouseDeltaY);

	if (mouseDeltaX || mouseDeltaY)
		testPlayer.Rotate(7.f*mouseDeltaY*game->dt, 7.f*mouseDeltaX*game->dt);
	
	
	ViewMat = testPlayer.lookAtMat4();

	mat4 mvp = ProjectionMat * ViewMat;
	glUniformMatrix4fv(mvpUniformAttrib, 1, GL_FALSE, value_ptr(mvp));

	glUniform1f(timeUniformAttrib, game->time);

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
