#pragma once
#include "glm.hpp"
#include "AndroidApplication.h"

namespace Engine {

    class Input {
    private:

    public:

        glm::ivec2 pointerPosition;
        glm::ivec2 pointerDelta;

        Input(){}
        ~Input(){}
        void init();
        void handleInput();
        void handleMotionEvents(android_input_buffer* inputBuffer);
        void handleKeyEvents(android_input_buffer* inputBuffer);

    };
}