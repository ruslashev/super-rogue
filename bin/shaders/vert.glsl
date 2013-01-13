#version 120

uniform mat4 mvp;

attribute vec2 vposition;
attribute vec2 vtexcoords;

varying vec2 texcoords;

void main()
{
	texcoords = vtexcoords;
	gl_Position = mvp * vec4(vposition, 0.0, 1.0);
}
