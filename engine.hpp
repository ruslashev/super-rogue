#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/noise.hpp>
#include <cstdio>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

// Drawing stuff
class renderer
{
private:
	glm::mat4 model, view, projection;
	GLuint vertexShader, fragmentShader, shaderProgram;
	
	double time, oldTime, dt, newTime, frameTime;
public:
	GLint posAttrib, mvpUniform;
	renderer(int wind_width, int wind_height, std::string title);
	~renderer();
	
	void init(int wind_width, int wind_height, std::string title);
	
	void startMainLoop();
	void load();
	void draw();
	void update();
	
	void loadShader(GLenum type, GLuint& shader, std::string filename);
};

class mesh
{
private:
	GLuint vbo_vertices, ibo_indices;
	GLint *posAttrib;
public:
	std::vector<glm::vec2> vertices;
	std::vector<ushort> indices;
	std::vector<glm::vec2> texCoords;
	
	mesh(GLint posAttr)
	{
		vbo_vertices = 0;
		ibo_indices = 0;
		
		posAttrib = &posAttr;
	}
	~mesh()
	{
		if (vbo_vertices != 0) { glDeleteBuffers(1, &vbo_vertices); }
		if (ibo_indices != 0) { glDeleteBuffers(1, &ibo_indices); }
		
		posAttrib = NULL;
	}
	
	void upload()
	{
		if (this->vertices.size() > 0)
		{
			glGenBuffers(1, &this->vbo_vertices);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices);
			glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(this->vertices[0]), this->vertices.data(), GL_STATIC_DRAW);
		}
				
		if (this->indices.size() > 0)
		{
			glGenBuffers(1, &this->ibo_indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices[0]), this->indices.data(), GL_STATIC_DRAW);
		}
	}
	
	void draw(GLenum drawMode = GL_TRIANGLES)
	{
		if (this->vbo_vertices != 0)
		{
			glEnableVertexAttribArray(*posAttrib);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices);
			glVertexAttribPointer(*posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
		
		if (this->ibo_indices != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo_indices);
			int size;
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glDrawElements(drawMode, size/sizeof(ushort), GL_UNSIGNED_SHORT, 0);
		} else {
			glDrawArrays(drawMode, 0, this->vertices.size());
		}
		
		if (this->vbo_vertices != 0) { glDisableVertexAttribArray(*posAttrib); }
	}
};
