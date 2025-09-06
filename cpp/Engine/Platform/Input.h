#pragma once
#include "glm.hpp"
#include "AppSurface.h"

#if PLATFORM == ANDROID
#include "AndroidInput.h"
#elif PLATFORM == WIN
#include "GlfwInput.h"
#endif

namespace Engine {

    class Input {
    private:

        AppSurface* appSurface;

#if PLATFORM == ANDROID
        AndroidInput input;
#elif PLATFORM == WIN
        GlfwInput input;
#endif

    public:

        Input(){}
        ~Input(){}

        void init(AppSurface* appSurface);
        void update();

        const glm::ivec2& getPointerDelta() const;
        const glm::ivec2& getPointerPosition() const;
        void getPointerPositionNormalized(glm::vec2& position);

        bool getPointerDown();
        bool getPointerPress();
        bool getPointerUp();
        bool getPointerClick();

#if PLATFORM == WIN
        bool getButtonDown(InputCode inputCode);
        bool getButtonPress(InputCode inputCode);
        bool getButtonUp(InputCode inputCode);
        bool getButtonClick(InputCode inputCode);
#elif PLATFORM == ANDROID
        bool getScreenDown(unsigned int index);
        bool getScreenPress(unsigned int index);
        bool getScreenUp(unsigned int index);
        bool getScreenClick(unsigned int index);
#endif
    };
}