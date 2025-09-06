#pragma once

#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"

namespace Engine {

	// buradan gelebilecek butun data triple buffere yazilacak

	class GlfwContext {
	private:

		GLFWmonitor* monitor;

	public:

		GLFWwindow* GLFW_window;
		const GLFWvidmode* mode;

		GlfwContext() {}
		~GlfwContext() {}

		void init();
		void makeContextCurrent();
		bool shouldClose();
		void pollEvents();
		void swapBuffers();
		void destroy();
		void setTitle(const char* title);
		void getScreenSize(glm::ivec2& screenSize);
	};
}