#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1280
#define HEIGHT 720

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return 1;
	}

	auto window = glfwCreateWindow(WIDTH, HEIGHT, "schmuhscheiß", nullptr, nullptr);

	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
