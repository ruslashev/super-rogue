#version 120

uniform mat4 mvp;

attribute vec2 vposition;

varying vec2 position;

void main()
{
	position = vposition;
	gl_Position = mvp * vec4(vposition, 0.0, 1.0);
}
