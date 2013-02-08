#version 120

varying vec3 position;
uniform float time;

void main() {
	gl_FragColor = vec4(vec3(mod(position.x*5.0, 1.0)), 1.0);
}