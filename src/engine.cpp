#include "engine.hpp"

renderer::renderer(int wind_width, int wind_height, std::string title)
{
	init(wind_width, wind_height, title);
}

void renderer::init(int wind_width, int wind_height, std::string title)
{
	if (!glfwInit()) { std::cerr << "Failed to initialize GLFW\n"; exit(1); }
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	if (!glfwOpenWindow(wind_width, wind_height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) { std::cerr << "Failed to open window\n"; exit(1); }
	glfwSetWindowTitle(title.c_str());
	GLFWvidmode videoMode;
	glfwGetDesktopMode(&videoMode);
	glfwSetWindowPos(videoMode.Width/2 - wind_width/2, videoMode.Height/2 - wind_height/2);
	glfwSwapInterval(1);
	
	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) { std::cerr << "GLEW failed to initialize. Error string:\n" << glewGetErrorString(glewInitStatus) << std::endl; exit(1); }
	
	glViewport(0, 0, wind_width, wind_height);

	glPointSize(5.0f);

	loadShader(GL_VERTEX_SHADER, vertexShader, "shaders/vert.glsl");
	loadShader(GL_FRAGMENT_SHADER, fragmentShader, "shaders/frag.glsl");
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	GLint successfulLink = GL_FALSE;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successfulLink);
	if (!successfulLink) { std::cerr << "Failed to link shader programn" << std::endl; exit(1); }
	glUseProgram(shaderProgram);
	posAttrib = glGetAttribLocation(shaderProgram, "vposition");
	texAttrib = glGetAttribLocation(shaderProgram, "vtexcoords");
}

void renderer::loadShader(GLenum type, GLuint& shader, std::string filename)
{
	std::ifstream filestream (filename.c_str());
	if (!filestream.good()) { std::cerr << "Failed to open shader \"" << filename << "\"\n"; exit(1); }

	std::string str;
	filestream.seekg(0, std::ios::end);
	str.resize(filestream.tellg());
	filestream.seekg(0, std::ios::beg);
	filestream.read(&str[0], str.size());
	filestream.close();

	const char* source = str.c_str();
	
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	
	GLint compileSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	char compileLog[513];
	if (compileSuccess == GL_FALSE) { glGetShaderInfoLog(shader, 512, NULL, compileLog); std::cerr << "Shader \"" << filename << "\" failed to compile. Error log:\n" << compileLog; glDeleteShader(shader); exit(1); }
}

renderer::~renderer()
{
	cleanup();

	glDetachShader(shaderProgram, vertexShader);	
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	glfwCloseWindow();
	glfwTerminate();
}