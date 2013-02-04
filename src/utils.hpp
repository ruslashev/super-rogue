#ifndef UTILS_HPP
#define UTILS_HPP

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/noise.hpp>
#include <ctime>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

bool LoadShader(GLenum type, GLuint& shader, const char* filename);

bool LinkShaderProgram(GLuint program);

#endif