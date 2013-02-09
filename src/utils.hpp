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
using namespace glm;

bool LoadShader(GLenum type, GLuint& shader, const char* filename);

bool LinkShaderProgram(GLuint program);

typedef unsigned char byte;

void GetMouseDeltas(int windowWidth, int windowHeight, float smoothing, int& deltaX, int& deltaY);

template<class T> static inline T toRadians(T x) { return (x*M_PI)/180; }
template<class T> static inline T toDegrees(T x) { return (x*180)/M_PI; }

#endif