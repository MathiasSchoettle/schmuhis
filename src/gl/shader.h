#pragma once

#include <string>
#include <map>
#include <GL/glew.h>

class shader {
	GLuint id = 0;
	std::string name;
	std::map<GLenum, std::string> source_files;

	void compile();
	GLuint compile_shader(GLenum type);

public:
	shader(std::string name, std::string vertex_source, std::string fragment_source);
	~shader();

	void bind();
	void unbind();

	shader(const shader &shader) = delete;

	void uniform(const std::string &name, const glm::vec3 &val);
	void uniform(const std::string &name, const glm::mat4 &matrix);
};