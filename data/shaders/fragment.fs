#version 120

varying vec3 position;

void main()
{	
	gl_FragColor = vec4(vec3(sin(position.x)), 1.0);
}
