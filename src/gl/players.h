#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.h"

class players {
	GLuint vbo, vao, ebo;
	glm::vec3 first_color, second_color;
	shader *player_shader;

public:
	players(glm::vec3 first_color, glm::vec3 second_color);
	~players();
	void draw_players(glm::vec2 first_pos, glm::vec2 second_pos);
};