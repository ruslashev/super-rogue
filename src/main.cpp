#include "engine.hpp"
#include "main.hpp"

std::vector<mesh> meshes;

int main()
{
	renderer drawman(800, 600, "pew pew pew");

	meshes.push_back(mesh(drawman.posAttrib));
	
	meshes.at(0).vertices.push_back(glm::vec2(0.f, 0.f));
	meshes.at(0).vertices.push_back(glm::vec2(512.f, 0.f));
	meshes.at(0).vertices.push_back(glm::vec2(512.f, 512.f));
	meshes.at(0).vertices.push_back(glm::vec2(0.f, 512.f));
	meshes.at(0).upload();

	drawman.startMainLoop();

	return 0;
}

void renderer::update()
{	
	model = glm::mat4();

	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(projection));
}
void renderer::draw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::vector<mesh>::iterator i = meshes.begin(); i != meshes.end(); i++)
	{
		i->draw(GL_QUADS);
	}

	glfwSwapBuffers();
}