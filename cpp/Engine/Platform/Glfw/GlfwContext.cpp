#include "pch.h"
#include "GlfwContext.h"

namespace Engine {

	
	void GlfwContext::init() {

		if (!glfwInit())
			fprintf(stderr, "Failed to initialize GLFW\n");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		monitor = glfwGetPrimaryMonitor();
		mode = glfwGetVideoMode(monitor);

		//GLFW_window = glfwCreateWindow(mode->width, mode->height, "Application", NULL, NULL); // windowed
		GLFW_window = glfwCreateWindow(mode->width, mode->height, "Application", monitor, NULL); // fullscreen

		glfwMaximizeWindow(GLFW_window);
		glfwMakeContextCurrent(GLFW_window);

		glfwSetInputMode(GLFW_window, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(GLFW_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void GlfwContext::makeContextCurrent() {

		glfwMakeContextCurrent(GLFW_window);
	}

	bool GlfwContext::shouldClose() {

		return glfwGetKey(GLFW_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(GLFW_window);
	}

	void GlfwContext::pollEvents() {

		glfwPollEvents();
	}

	void GlfwContext::swapBuffers() {

		glfwSwapBuffers(GLFW_window);
	}

	void GlfwContext::destroy() {

		if (GLFW_window) {
			glfwDestroyWindow(GLFW_window);
			GLFW_window = nullptr;
		}
		glfwTerminate();
	}

	void GlfwContext::setTitle(const char* title) {

		glfwSetWindowTitle(GLFW_window, title);
	}

	void GlfwContext::getScreenSize(glm::ivec2& screenSize) {

		screenSize = glm::ivec2(mode->width, mode->height);
	}

}