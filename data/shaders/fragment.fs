#version 120

varying vec3 position;

uniform float time;
uniform vec3 playerPos;

void main() {
	gl_FragColor = vec4(vec3(distance(playerPos, position)/10.), 1.0);
}