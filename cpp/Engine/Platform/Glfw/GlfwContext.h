#pragma once

#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"

namespace Engine {

	class GlfwContext {
	private:

	public:

		GLFWwindow* GLFW_window;
		glm::ivec2 screenSize;
		bool aspectChanged;
		std::mutex mtx;

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
		float getAspectRatio();
		void checkScreenSize();
		bool getAspectChanged();
	};
}