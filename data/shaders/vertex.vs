#version 120

uniform mat4 mvp;

attribute vec3 vposition;

varying vec3 position;

void main()
{
	position = vposition;
	gl_Position = mvp * vec4(vposition, 1.0);
}