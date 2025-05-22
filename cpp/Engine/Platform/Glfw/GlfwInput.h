#pragma once
#include "glm.hpp"
#include "GlfwContext.h"

namespace Engine {

    enum class GlfwInputCode {
        Q = GLFW_KEY_Q,
        W = GLFW_KEY_W,
        E = GLFW_KEY_E,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,
        Space = GLFW_KEY_SPACE,
        LShift = GLFW_KEY_LEFT_SHIFT,
        Mouse_Left = GLFW_MOUSE_BUTTON_LEFT,
        Mouse_Right = GLFW_MOUSE_BUTTON_RIGHT,
        Mouse_Middle = GLFW_MOUSE_BUTTON_MIDDLE
    };

    enum class InputCode {
        Mouse_Left      = 0,
        Mouse_Right     = 1,
        Mouse_Middle    = 2,
        Q               = 3,
        W               = 4,
        E               = 5,
        A               = 6,
        S               = 7,
        D               = 8,
        Space           = 9,
        LShift          = 10
    };

    class GlfwInput {
    private:

        GLFWwindow* GLFW_window;

    public:

        glm::i16vec2 pointerPosition;
        glm::i16vec2 pointerDelta;

        float scrollDelta = 0.f;

        unsigned int pressBuffer;
        unsigned int pressLockBuffer;
        unsigned int upBuffer;
        unsigned int upLockBuffer;
        unsigned int downBuffer;

        GlfwInput(){}
        ~GlfwInput(){}
        void init(GLFWwindow* GLFW_window);
        void update();
        bool getButtonDown(InputCode inputCode);
        bool getButtonPress(InputCode inputCode);
        bool getButtonUp(InputCode inputCode);
        void setCursorPos(glm::i16vec2 cursorPos);
        void getCursorPos(glm::i16vec2& cursorPos);
        void setCursorVisible(bool visible);

    };
}