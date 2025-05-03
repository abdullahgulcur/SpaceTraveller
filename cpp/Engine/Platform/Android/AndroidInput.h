#pragma once
#include "glm.hpp"
#include "AndroidApplication.h"

namespace Engine {

    class Input;

    class AndroidInput {
    private:

    public:

        // add pointer position etc ... 

        AndroidInput(){}
        ~AndroidInput(){}
        void init();
        void update(Input& input);
        void handleMotionEvents(Input& input, android_input_buffer* inputBuffer);
        void handleKeyEvents(Input& input, android_input_buffer* inputBuffer);
    };
}