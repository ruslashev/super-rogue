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
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <forward_list>

using namespace std;
using namespace glm;

bool LoadShader(GLenum type, GLuint& shader, const char* filename);

bool LinkShaderProgram(GLuint program);

typedef unsigned char byte;

void GetMouseDeltas(int windowWidth, int windowHeight, float smoothing, int& deltaX, int& deltaY);

template<class T> inline T toRadians(T x) { return (x*M_PI)/180; }
template<class T> inline T toDegrees(T x) { return (x*180)/M_PI; }

vector<vec3> MakeBox(vec3 position, float size);

struct AABB
{
	vec3 position;

	float width;
	float height;
	float depth;
};

bool vec3InAABB(vec3 point, AABB box);
bool AABBinAABB(AABB box, AABB box2);

#endif