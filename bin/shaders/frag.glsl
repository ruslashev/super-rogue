#version 120

varying vec2 position;
varying vec2 texcoords;

uniform sampler2D tile;

void main()
{	
	gl_FragColor = texture2D(tile, texcoords);
}
