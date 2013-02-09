#version 120

varying vec3 position;
uniform float time;

void main() {
	gl_FragColor = vec4(vec3(sin(position.x*10.0)*0.5+0.5), 1.0);
}