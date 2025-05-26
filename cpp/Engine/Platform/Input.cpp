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

        input.update();


//#if PLATFORM == ANDROID
//        input.update();
//#elif PLATFORM == WIN
//        input.update();
//
//#endif

    }

    const glm::ivec2& Input::getPointerDelta() const {
        return input.pointerDelta;
    }

    const glm::ivec2& Input::getPointerPosition() const {
        return input.pointerPosition;
    }

    void Input::getPointerPositionNormalized(glm::vec2& position) {
        glm::u16vec2 size;
        Core::getInstance()->appSurface.getSize(size);
        position.x = (input.pointerPosition.x / (float)size.x) * 2.0f - 1.0f;
        //position.y = (input.pointerPosition.y / (float)size.y) * 2.0f - 1.0f;
        position.y = 1.0f - (input.pointerPosition.y / (float)size.y) * 2.0f;
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

#endif

}