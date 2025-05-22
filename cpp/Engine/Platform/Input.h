#pragma once
#include "glm.hpp"

#if PLATFORM == ANDROID
#include "AndroidInput.h"
#elif PLATFORM == WIN
#include "GlfwInput.h"
#endif

namespace Engine {

    class Input {
    private:

#if PLATFORM == ANDROID
        AndroidInput input;
#elif PLATFORM == WIN
        GlfwInput input;
#endif

    public:

        glm::ivec2 pointerPosition;
        glm::ivec2 pointerDelta;

#if PLATFORM == WIN

#endif

        Input(){}
        ~Input(){}
        void init();
        void update();

        const glm::ivec2& getPointerDelta() const;
        const glm::ivec2& getPointerPosition() const;

#if PLATFORM == WIN
        bool getButtonDown(InputCode inputCode);
        bool getButtonPress(InputCode inputCode);
        bool getButtonUp(InputCode inputCode);

#endif

    };
}