#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 uvOut;

void main() {
	uvOut = uv;
	gl_Position = vec4(pos, 1.0);
}
