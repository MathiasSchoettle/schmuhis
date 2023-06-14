#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "players.h"

players::players(glm::vec3 first_color, glm::vec3 second_color) 
	: first_color(first_color), second_color(second_color) {
	
	float vertices[] = {
		 1.0f,  1.0f,
		 1.0f, -1.0f,
		-1.0f, -1.0f,
		-1.0f,  1.0f,
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	player_shader = new shader("player shader", "shaders/players.vert", "shaders/players.frag");
}

players::~players() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	delete player_shader;
}

void players::draw_players(glm::vec2 first_pos, glm::vec2 second_pos) {
	
	angle += 1.0f;
	angle = (int) angle % 360;

	auto matrix = glm::mat4(1.0f);
	matrix = glm::scale(matrix, glm::vec3(0.2));

	player_shader->bind();
	player_shader->uniform("transform", matrix);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	player_shader->unbind();
}