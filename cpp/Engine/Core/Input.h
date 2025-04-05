#pragma once
#include "glm.hpp"
#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace Engine {

    class Input {
    private:

        android_app *app_;

    public:

        glm::ivec2 pointerPosition;
        glm::ivec2 pointerDelta;

        Input(){}
        ~Input(){}
        void init(android_app *app_);
        void handleInput();
        void handleMotionEvents(android_input_buffer* inputBuffer);
        void handleKeyEvents(android_input_buffer* inputBuffer);

    };
}