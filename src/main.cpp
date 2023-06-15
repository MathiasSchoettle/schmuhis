#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "gl/shader.h"
#include "gl/tri.h"
#include "netcode/NetworkComponent.h"

#define WIDTH 1280
#define HEIGHT 1280

auto pos_1 = glm::vec2(0);
auto pos_2 = glm::vec2(0);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void movement(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos_1 += glm::vec2(0, 0.1);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos_1 -= glm::vec2(0.1, 0);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos_1 -= glm::vec2(0, 0.1);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos_1 += glm::vec2(0.1, 0);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pos_2 += glm::vec2(0, 0.1);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		pos_2 -= glm::vec2(0.1, 0);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pos_2 -= glm::vec2(0, 0.1);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		pos_2 += glm::vec2(0.1, 0);
}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(WIDTH, HEIGHT, "schmuhscheiß", nullptr, nullptr);

	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	players p(glm::vec3(0.2), glm::vec3(0.6));

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		movement(window);
		p.draw_players(pos_1, pos_2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
