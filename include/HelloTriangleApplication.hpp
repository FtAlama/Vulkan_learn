#ifndef HELLO_TRIANGLE_HPP

#define HELLO_TRIANGLE_HPP

#include "GLFW/glfw3.h"

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
	HelloTriangleApplication() : window(nullptr) {}
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }
	~HelloTriangleApplication() {}

private:
	GLFWwindow* window;
  
	void initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan test", nullptr, nullptr);
	}
  
	void initVulkan() {}
  
	void mainLoop() {
		while(!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}
  
	void cleanup() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

#endif
