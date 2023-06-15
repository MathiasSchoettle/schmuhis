#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

std::string read_source(const std::string &filepath) {
	std::ifstream file("./" + filepath);
	if (file.is_open()) {
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}
	return std::string();
}

GLuint shader::compile_shader(GLenum type) {
	auto source = read_source(source_files[type]);

	if (source.empty()) {
		std::cerr << "Shader source of " << source_files[type] << " is empty" << std::endl;
		return 0;
	}

	GLuint shader_id = glCreateShader(type);
	auto src = source.c_str();
	glShaderSource(shader_id, 1, &src, nullptr);
	glCompileShader(shader_id);

	GLint success = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (success == GL_TRUE) return shader_id;

	// on failure, print error log and return empty id
	GLint length = 0;
	std::string message = "Error while compiling shader " + name + ":\n";
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

	char *log = (char*) malloc(length);
	glGetShaderInfoLog(shader_id, length, nullptr, log);
	message += log;
	free(log);

	message += "\nsource:\n" + source;
	std::cerr << message << std::endl;

	glDeleteShader(shader_id);
	return 0;
}

void shader::compile() {
	GLuint program = glCreateProgram();
	auto vertex_shader = compile_shader(GL_VERTEX_SHADER);
	auto fragment_shader = compile_shader(GL_FRAGMENT_SHADER);

	if (!vertex_shader || !fragment_shader) {
		glDeleteProgram(program);
		return;
	}

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	GLint success = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	if (success == GL_TRUE) {
		if (glIsProgram(id)) glDeleteProgram(id);
		id = program;
	} else {
		GLint length = 0;
		std::string message = "Failed linking of " + name + "\n";
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		char *log = (char*) malloc(length);
		glGetProgramInfoLog(program, length, nullptr, log);
		message += log;
		free(log);

		glDeleteProgram(program);

		std::cerr << message << std::endl;
	}
}

shader::shader(std::string name, std::string vertex_source, std::string fragment_source) : name(name) {
	source_files[GL_VERTEX_SHADER] = vertex_source;
	source_files[GL_FRAGMENT_SHADER] = fragment_source;
	compile();
}

shader::~shader() {
	if (glIsProgram(id))
		glDeleteProgram(id);
}

void shader::bind() {
	glUseProgram(id);
}

void shader::unbind() {
	glUseProgram(0);
}

void shader::uniform(const std::string &name, const glm::vec3 &val) {
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform3f(loc, val.x, val.y, val.z);
}

void shader::uniform(const std::string &name, const glm::mat4 &val) {
	int loc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}