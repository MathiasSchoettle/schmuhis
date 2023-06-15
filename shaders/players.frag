#version 460

out vec4 color;

uniform vec3 player_color;

void main() {
	color = vec4(player_color, 1.0);
}