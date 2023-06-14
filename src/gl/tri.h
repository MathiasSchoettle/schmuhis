#pragma once

#include <GL/glew.h>

class tri {
	float *vertices;

public:
	GLuint vbo, vao;

	tri();
	~tri();
	void draw();
};