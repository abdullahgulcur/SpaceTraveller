#include "pch.h"
#include "Input.h"

#if PLATFORM == WIN
#include "Core.h"
#endif

namespace Engine {

    void Input::init() {

        pointerDelta = glm::ivec2(0);

#if PLATFORM == ANDROID
        input.init();
#elif PLATFORM == WIN
        input.init(Core::getInstance()->appSurface.glfwContext.GLFW_window);
#endif
    }

    void Input::update(){

#if PLATFORM == ANDROID
        input.update(*this);
#elif PLATFORM == WIN
        input.update();

#endif

    }

#if PLATFORM == WIN

    bool Input::getButtonDown(InputCode inputCode) {
        return input.getButtonDown(inputCode);
    }

    bool Input::getButtonPress(InputCode inputCode) {
        return input.getButtonPress(inputCode);
    }

    bool Input::getButtonUp(InputCode inputCode) {
        return input.getButtonUp(inputCode);
    }

    const glm::ivec2& Input::getPointerDelta() const {
        return input.pointerDelta;
    }

    const glm::ivec2& Input::getPointerPosition() const {
        return input.pointerPosition;
    }

#endif

}