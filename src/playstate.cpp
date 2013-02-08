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

	Projection = perspective(45.f, (float)game->windowWidth/(float)game->windowHeight, 1.f, 100.f);
	mvpUniform = glGetUniformLocation(shaderProgram, "mvp");
	timeUniform = glGetUniformLocation(shaderProgram, "time");

	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			// byte tile = gamemap[x][y];

			int tileSize = 1;
			testEnt.vertices.push_back(vec3(x*tileSize			, 0, y*tileSize			));
			testEnt.vertices.push_back(vec3(x*tileSize			, 0, y*tileSize+tileSize));
			testEnt.vertices.push_back(vec3(x*tileSize+tileSize	, 0, y*tileSize			));
			testEnt.vertices.push_back(vec3(x*tileSize+tileSize	, 0, y*tileSize			));
			testEnt.vertices.push_back(vec3(x*tileSize+tileSize	, 0, y*tileSize+tileSize));
			testEnt.vertices.push_back(vec3(x*tileSize			, 0, y*tileSize+tileSize));
		}

	testEnt.Upload();

	testEnt.SetPosition(vec3(0, 0, 0));

	testPlayer.SetPosition(vec3(0, 4, 0));

	return true;
}

void PlayState::Update(GameEngine* game)
{
	float movingHowMany = 0;
	if (glfwGetKey('W'))
		movingHowMany = 0.05;
	if (glfwGetKey('S'))
		movingHowMany = -0.05;

	if (movingHowMany)
	{
    	float lx = cos(testPlayer.m_yaw)*cos(testPlayer.m_pitch);
    	float ly = sin(testPlayer.m_pitch);
    	float lz = sin(testPlayer.m_yaw)*cos(testPlayer.m_pitch);

		vec3 oldPos = testPlayer.GetPosition();
		testPlayer.SetPosition(vec3(oldPos.x + movingHowMany*lx, oldPos.y + movingHowMany*ly, oldPos.z + movingHowMany*lz));
	}

	int mouseDeltaX, mouseDeltaY;
	GetMouseDeltas(game->windowWidth, game->windowHeight, 2.7f, mouseDeltaX, mouseDeltaY);

	if (mouseDeltaX)
		testPlayer.m_yaw += M_PI/180*0.2*mouseDeltaX;
	if (mouseDeltaY)
		testPlayer.m_pitch -= M_PI/180*0.2*mouseDeltaY;
	
	/*
	static int con = 0;
	con++;
	if (con >= 10)
	{
		printf("p %f\t\t y %f\n", testPlayer.m_pitch, testPlayer.m_yaw);
		con = 0;
	}
	*/
	
	vec3 pos = testPlayer.GetPosition();
	View = lookAt(pos, vec3(pos.x+cos(testPlayer.m_yaw)*cos(testPlayer.m_pitch), pos.y+sin(testPlayer.m_pitch), pos.z+sin(testPlayer.m_yaw)*cos(testPlayer.m_pitch)), vec3(0, 1, 0));

	mat4 mvp = Projection * View;
	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, value_ptr(mvp));

	glUniform1f(timeUniform, game->time);

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
