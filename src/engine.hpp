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

class renderer
{
private:
	
public:
	glm::mat4 model, view, projection;
	GLuint vertexShader, fragmentShader;
	GLint posAttrib, mvpUniform, texAttrib;
	GLuint shaderProgram;

	renderer(int wind_width, int wind_height, std::string title);
	~renderer();
	
	void init(int wind_width, int wind_height, std::string title);
	
	void loadShader(GLenum type, GLuint& shader, std::string filename);
	
	void cleanup();
};

class mesh
{
private:
	GLuint vbo_vertices, ibo_indices, vbo_texcoords;
public:
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<ushort> indices;
	
	mesh()
	{
		vbo_vertices = 0;
		vbo_texcoords = 0;
		ibo_indices = 0;
	}
	~mesh()
	{
		if (vbo_vertices != 0) { glDeleteBuffers(1, &vbo_vertices); }
		if (vbo_texcoords != 0) { glDeleteBuffers(1, &vbo_texcoords); }
		if (ibo_indices != 0) { glDeleteBuffers(1, &ibo_indices); }
	}
	
	void upload()
	{
		if (vertices.size() > 0)
		{
			glGenBuffers(1, &vbo_vertices);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
		}

		if (texCoords.size() > 0)
		{
			glGenBuffers(1, &vbo_texcoords);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
			glBufferData(GL_ARRAY_BUFFER, texCoords.size()*sizeof(texCoords[0]), texCoords.data(), GL_STATIC_DRAW);
		}
				
		if (indices.size() > 0)
		{
			glGenBuffers(1, &ibo_indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
		}
	}
	
	void draw(GLint posAttrib, GLint texAttrib, GLenum drawMode = GL_TRIANGLES)
	{
		if (vbo_vertices != 0)
		{
			glEnableVertexAttribArray(posAttrib);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
		
		if (vbo_texcoords != 0)
		{
			glEnableVertexAttribArray(texAttrib);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
		
		if (ibo_indices != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_indices);
			int size;
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glDrawElements(drawMode, size/sizeof(ushort), GL_UNSIGNED_SHORT, 0);
		} else {
			glDrawArrays(drawMode, 0, vertices.size());
		}
		
		if (vbo_vertices != 0) { glDisableVertexAttribArray(posAttrib); }
		if (vbo_texcoords != 0) { glDisableVertexAttribArray(texAttrib); }
	}
};
