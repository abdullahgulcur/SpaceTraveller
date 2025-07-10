#pragma once

#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"

namespace Engine {

	class GlfwContext {
	private:

		GLFWmonitor* monitor;

	public:

		GLFWwindow* GLFW_window;
		const GLFWvidmode* mode;

		GlfwContext() {}
		~GlfwContext() {}

		void init();
		bool shouldClose();
		void pollEvents();
		void swapBuffers();
		void destroy();
		void setTitle(const char* title);
		/*void setCursorPos(glm::u16vec2 cursorPos);
		void getCursorPos(glm::u16vec2& cursorPos);*/
		void getScreenSize(glm::ivec2& screenSize);
		//void setCursorVisible(bool visible);
		/*static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);*/
	};
}