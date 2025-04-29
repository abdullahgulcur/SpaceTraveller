#pragma once
#include "glm.hpp"
#include "AndroidApplication.h"
#include "Input.h"

namespace Engine {

    class AndroidInput {
    private:

    public:

        AndroidInput(){}
        ~AndroidInput(){}
        void init(Input& input);
        void update(Input& input);
        void handleMotionEvents(Input& input, android_input_buffer* inputBuffer);
        void handleKeyEvents(Input& input, android_input_buffer* inputBuffer);
    };
}