#include "pch.h"
#include "GlfwContext.h"
//#include "core.h"

namespace Engine {

	
	void GlfwContext::init() {

		if (!glfwInit())
			fprintf(stderr, "Failed to initialize GLFW\n");

		//glfwWindowHint(GLFW_SAMPLES, 4);
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

		//glfwSetKeyCallback(GLFW_window, key_callback);
		//glfwSetMouseButtonCallback(GLFW_window, mouseButtonCallback);
		//glfwSetScrollCallback(GLFW_window, mouseScrollCallback);
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


	//void GlfwContext::setCursorPos(glm::u16vec2 cursorPos) {

	//	glfwSetCursorPos(GLFW_window, cursorPos.x, cursorPos.y);
	//}

	//void GlfwContext::getCursorPos(glm::u16vec2& cursorPos) {

	//	double xPos, yPos;
	//	glfwGetCursorPos(GLFW_window, &xPos, &yPos);
	//	cursorPos = glm::u16vec2(xPos, yPos);
	//}

	void GlfwContext::getScreenSize(glm::ivec2& screenSize) {

		screenSize = glm::ivec2(mode->width, mode->height);
	}

	//void GlfwContext::setCursorVisible(bool visible) {

	//	int value = visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN;
	//	glfwSetInputMode(GLFW_window, GLFW_CURSOR, value);
	//}

	//void GlfwContext::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	//	//Core::getInput()->handleKeyboardInput(key, action);
	//}

	//void GlfwContext::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	//	//Core::getInput()->handleMouseInput(button, action);
	//}

	//void GlfwContext::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

	//	//Core::getInput()->handleMouseScrollInput(yoffset);
	//}

}