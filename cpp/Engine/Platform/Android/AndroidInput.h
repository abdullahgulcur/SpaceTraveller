#pragma once
#include "glm.hpp"
#include "AndroidApplication.h"

namespace Engine {

    class AndroidInput {
    private:

    public:

        glm::i16vec2 pointerPosition;
        glm::i16vec2 pointerDelta;

        AndroidInput(){}
        ~AndroidInput(){}
        void init();
        void update();
        void handleMotionEvents(android_input_buffer* inputBuffer);
        void handleKeyEvents(android_input_buffer* inputBuffer);
    };
}