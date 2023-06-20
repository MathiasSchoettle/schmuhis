#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "gl/shader.h"
#include "gl/players.h"
#include "netcode/network_component.h"

#define WIDTH 1280
#define HEIGHT 720

auto pos_1 = glm::vec2(30, 0);
auto pos_2 = glm::vec2(15, 0);
float velocity_1 = 0;
float velocity_2 = 0;


static void help()
{
    std::cout << "Usage:\n";
    std::cout << "app [options]" << std::endl; 
    
    std::cout << "options:" << std::endl;
	std::cout << "\t -m , selects connection mode (Server, Client), default is server" << std::endl;
    std::cout << "\t -ip , enter IP-Address of the server, only possible in client mode" << std::endl;
    exit(1);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void movement(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && pos_1.y <= 0)
		velocity_1 = 0.7;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && pos_2.y <= 0)
		velocity_2 = 0.7;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos_1 -= glm::vec2(0.1, 0);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos_1 += glm::vec2(0.1, 0);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		pos_2 -= glm::vec2(0.1, 0);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		pos_2 += glm::vec2(0.1, 0);
	
	if (velocity_1 != 0) {
		pos_1.y += velocity_1;
		velocity_1 -= 0.025;
	}

	if (pos_1.y < 0) {
		pos_1.y = 0;
		velocity_1 = 0;
	}

	if (velocity_2 != 0) {
		pos_2.y += velocity_2;
		velocity_2 -= 0.025;
	}

	if (pos_2.y < 0) {
		pos_2.y = 0;
		velocity_2 = 0;
	}
}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int connection_mode_selection(int argc, char* argv[]){
	if(strstr(argv[1], "-m") !=0){
		if(argc > 2){
			if((strstr(argv[2], "client") != 0)){
				std::cout << "client mode selected!" << std::endl;
				if((argc > 3) && (strstr(argv[3], "-ip") != 0)){

					if((strstr(argv[4], "") == 0)){
						std::cout << "no server ip address provided!" << std::endl;
						return 1;
					}
					else
						std::cout << "trying to connect to following ip address: " << argv[4] << std::endl;
				}
				else{
					std::cout << "no server ip address provided!" << std::endl;
					return 1;
				}
			}
		}
		else{
			std::cout << "running in server mode!" << std::endl;
			return 1;
		}
	}	
	return 0;
}
int main(int argc, char* argv[]) {
	

	//---------[ check the arg count ]----------------------------------------
    if(argc < 2)
        std::cout << "running in server mode!" << std::endl;
    if(strstr(argv[1],"-h") != 0)
        help();
    if(strstr(argv[1],"-?") != 0)
		help();
	
	if(!connection_mode_selection(argc, argv)){
		std::cerr << "Failed to initialize connection!" << std::endl;
		return 1;
	}
	
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

	players p(glm::vec3(0.1, 0.8, 0.2), glm::vec3(0.6, 0.2, 0.7));

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		movement(window);
		p.draw_players(pos_1, pos_2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
