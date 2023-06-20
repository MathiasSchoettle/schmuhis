#version 460

layout(location = 0) in vec2 position;

uniform mat4 transform;
uniform mat4 proj;

void main() {
	gl_Position = proj * transform * vec4(position, 1.0, 1.0);
}