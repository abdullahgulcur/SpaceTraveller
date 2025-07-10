#include "pch.h"
#include "Input.h"
#include "Core.h"

#if PLATFORM == WIN
#endif

namespace Engine {

    void Input::init() {

#if PLATFORM == ANDROID
        input.init();
#elif PLATFORM == WIN
        input.init(Core::getInstance()->appSurface.glfwContext.GLFW_window);
#endif
    }

    void Input::update(){

        input.update();
    }

    const glm::ivec2& Input::getPointerDelta() const {

#if PLATFORM == ANDROID
        return input.pointerDelta[0];
#elif PLATFORM == WIN
        return input.pointerDelta;
#endif
    }

    const glm::ivec2& Input::getPointerPosition() const {

#if PLATFORM == ANDROID
        return input.pointerPosition[0];
#elif PLATFORM == WIN
        return input.pointerPosition;
#endif
    }

    void Input::getPointerPositionNormalized(glm::vec2& position) {

#if PLATFORM == ANDROID
        glm::ivec2 size;
        Core::getInstance()->appSurface.getSize(size);
        position.x = (input.pointerPosition[0].x / (float)size.x) * 2.0f - 1.0f;
        //position.y = (input.pointerPosition.y / (float)size.y) * 2.0f - 1.0f;
        position.y = 1.0f - (input.pointerPosition[0].y / (float)size.y) * 2.0f;
#elif PLATFORM == WIN
        glm::ivec2 size;
        Core::getInstance()->appSurface.getSize(size);
        position.x = (input.pointerPosition.x / (float)size.x) * 2.0f - 1.0f;
        //position.y = (input.pointerPosition.y / (float)size.y) * 2.0f - 1.0f;
        position.y = 1.0f - (input.pointerPosition.y / (float)size.y) * 2.0f;
#endif
    }

    bool Input::getPointerDown() {
#if PLATFORM == ANDROID
        return Input::getScreenDown(0);
#elif PLATFORM == WIN
        return Input::getButtonDown(InputCode::Mouse_Left);
#endif
    }

    bool Input::getPointerPress() {
#if PLATFORM == ANDROID
        return Input::getScreenPress(0);
#elif PLATFORM == WIN
        return Input::getButtonPress(InputCode::Mouse_Left);
#endif
    }

    bool Input::getPointerUp() {
#if PLATFORM == ANDROID
        return Input::getScreenUp(0);
#elif PLATFORM == WIN
        return Input::getButtonUp(InputCode::Mouse_Left);
#endif
    }

    bool Input::getPointerClick() {
#if PLATFORM == ANDROID
        return Input::getScreenClick(0);
#elif PLATFORM == WIN
        return Input::getButtonClick(InputCode::Mouse_Left);
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

    bool Input::getButtonClick(InputCode inputCode) {
        return input.getButtonClick(inputCode);
    }

#endif


#if PLATFORM == ANDROID

    bool Input::getScreenDown(unsigned int index) {
        return input.getScreenDown(index);
    }

    bool Input::getScreenPress(unsigned int index) {
        return input.getScreenPress(index);
    }

    bool Input::getScreenUp(unsigned int index) {
        return input.getScreenUp(index);
    }

    bool Input::getScreenClick(unsigned int index) {
        return input.getScreenClick(index);
    }

#endif

}