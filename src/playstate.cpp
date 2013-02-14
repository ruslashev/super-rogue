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
	{
		if (!LoadShader(GL_VERTEX_SHADER, vertexShader, "data/shaders/vertex.vs") ||
			!LoadShader(GL_FRAGMENT_SHADER, fragmentShader, "data/shaders/fragment.fs")) {
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
		pposUniformAttrib = glGetUniformLocation(shaderProgram, "playerPos");
	}
	
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			boxes.push_front(Drawable());
			
			boxes.front().m_vertices = MakeBox(1.f);
			boxes.front().SetPosition(vec3(2.f*x, 0, 2.f*y));
			boxes.front().m_collisionBox = AABB { boxes.front().GetPosition(), 1.f, 1.f, 1.f};

			boxes.front().Upload();
		}
	}

	testPlayer.SetPosition(vec3(0, 4, 0));

	return true;
}

void PlayState::Update(GameEngine* game)
{
	vec3 oldPos = testPlayer.GetPosition();
	testPlayer.Update(game->dt);
	for (auto b = boxes.begin(); b != boxes.end(); b++) {
		if (AABBinAABB(AABB { testPlayer.GetPosition(), 0.2f, 0.2f, 0.2f }, b->m_collisionBox)) {
			testPlayer.SetPosition(oldPos);
			break;
		}
	}


	ViewMat = testPlayer.LookAtMat4();
	glUniform1f(timeUniformAttrib, game->time);
	glUniform3f(pposUniformAttrib, testPlayer.GetPosition().x, testPlayer.GetPosition().y, testPlayer.GetPosition().z);

	if (glfwGetKey(GLFW_KEY_ESC))
		game->Quit();
}

void PlayState::Draw(GameEngine* game)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto b = boxes.begin(); b != boxes.end(); b++) {
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		b->modelMat = translate(mat4(1), b->GetPosition());
		glUniformMatrix4fv(mvpUniformAttrib, 1, GL_FALSE, value_ptr(ProjectionMat * ViewMat * b->modelMat));
		b->Draw();
		
		glDisableVertexAttribArray(posAttrib);
	}

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
