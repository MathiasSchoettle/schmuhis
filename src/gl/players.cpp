#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "players.h"

#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 12
#define GAME_WIDTH 160
#define GAME_HEIGHT 90

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

	auto model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 6, 0));
	model_matrix = glm::scale(model_matrix, glm::vec3(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2, 1));
	auto proj = glm::ortho<float>(0, GAME_WIDTH, 0, GAME_HEIGHT);
	player_shader->bind();
	player_shader->uniform("proj", proj);

	auto first_matrix = glm::translate(model_matrix, glm::vec3(first_pos.x, first_pos.y, 0));
	player_shader->uniform("player_color", first_color);
	player_shader->uniform("transform", first_matrix);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	auto second_matrix = glm::translate(model_matrix, glm::vec3(second_pos.x, second_pos.y, 0));
	player_shader->uniform("player_color", second_color);
	player_shader->uniform("transform", second_matrix);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	player_shader->unbind();
}