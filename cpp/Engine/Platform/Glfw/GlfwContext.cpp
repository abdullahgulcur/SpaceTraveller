#include "pch.h"
#include "GlfwContext.h"

namespace Engine {

	void GlfwContext::init() {

		if (!glfwInit())
			fprintf(stderr, "Failed to initialize GLFW\n");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwMainWindow = glfwCreateWindow(mode->width, mode->height, "SpaceTraveller", NULL, NULL); // windowed
		glfwMaximizeWindow(glfwMainWindow);

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		//glfwAsyncTextureGeneratorWindow = glfwCreateWindow(1, 1, "", nullptr, glfwMainWindow);

		glfwSetInputMode(glfwMainWindow, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(glfwMainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		screenSize = glm::ivec2(mode->width, mode->height);

		//GLFW_window = glfwCreateWindow(mode->width, mode->height, "Application", monitor, NULL); // fullscreen

	}

	void GlfwContext::makeContextCurrent() {

		glfwMakeContextCurrent(glfwMainWindow);
	}

	bool GlfwContext::shouldClose() {

		return glfwGetKey(glfwMainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(glfwMainWindow);
	}

	void GlfwContext::pollEvents() {

		glfwPollEvents();
	}

	void GlfwContext::swapBuffers() {

		glfwSwapBuffers(glfwMainWindow);
	}

	void GlfwContext::destroy() {

		if (glfwMainWindow) {
			glfwDestroyWindow(glfwMainWindow);
			glfwMainWindow = nullptr;
		}
		glfwTerminate();
	}

	void GlfwContext::setTitle(const char* title) {

		glfwSetWindowTitle(glfwMainWindow, title);
	}

	void GlfwContext::getScreenSize(glm::ivec2& screenSize) {
		std::lock_guard<std::mutex> lock(mtx);
		screenSize = this->screenSize;
	}

	float GlfwContext::getAspectRatio() {
		std::lock_guard<std::mutex> lock(mtx);
		if (screenSize.x == 0 || screenSize.y == 0)
			return 1.0f;
		return screenSize.x / (float)screenSize.y;
	}

	void GlfwContext::checkScreenSize() {
		std::lock_guard<std::mutex> lock(mtx);

		int width, height;
		glfwGetWindowSize(glfwMainWindow, &width, &height);

		if (width != screenSize.x || height != screenSize.y) {
			this->screenSize.x = width;
			this->screenSize.y = height;
			aspectChanged = true;
			return;
		}
		aspectChanged = false;
	}

	bool GlfwContext::getAspectChanged() {
		std::lock_guard<std::mutex> lock(mtx);
		return aspectChanged;
	}

}