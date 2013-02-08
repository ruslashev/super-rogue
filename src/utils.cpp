#include "utils.hpp"

bool LoadShader(GLenum type, GLuint& shader, const char* filename)
{
	std::ifstream fileStream (filename);
	if (!fileStream.good()) {
		fprintf(stderr, "Failed to open shader \"%s\"\n", filename);
		return false;
	}

	std::string str;
	fileStream.seekg(0, std::ios::end);
	str.resize(fileStream.tellg());
	fileStream.seekg(0, std::ios::beg);
	fileStream.read(&str[0], str.size());
	fileStream.close();

	const char* source = str.c_str();
	
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	
	GLint compileSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE) {		
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char compileLog[infoLogLength+1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, compileLog);
		fprintf(stderr, "Shader \"%s\" failed to compile. Error log:\n%s", filename, compileLog);
		glDeleteShader(shader);
		return false;
	}

	return true;
}

bool LinkShaderProgram(GLuint program)
{
	glLinkProgram(program);
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus) {
		fprintf(stderr, "Failed to link shader program\n");
		return false;
	}
	
	return true;
}

void GetMouseDeltas(int windowWidth, int windowHeight, float smoothing, int& deltaX, int& deltaY)
{
	int oldMouseX, oldMouseY, newMouseX, newMouseY;

	glfwGetMousePos(&oldMouseX, &oldMouseY);
	glfwSetMousePos(windowWidth/2, windowHeight/2);
	glfwGetMousePos(&newMouseX, &newMouseY);

	deltaX = (oldMouseX - newMouseX)/smoothing;
	deltaY = (oldMouseY - newMouseY)/smoothing;
}