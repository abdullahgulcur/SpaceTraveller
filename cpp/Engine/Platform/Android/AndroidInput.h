#pragma once
#include "glm.hpp"
#include "AndroidApplication.h"

namespace Engine {

    class AndroidInput {
    private:

    public:

        glm::i16vec2 pointerPositionLastPress[8];
        glm::i16vec2 pointerPosition[8];
        glm::i16vec2 pointerDelta[8];

        unsigned int pressBuffer;
        unsigned int pressLockBuffer;
        unsigned int upBuffer;
        unsigned int upLockBuffer;
        unsigned int downBuffer;
        unsigned int clickBuffer;


        AndroidInput(){}
        ~AndroidInput(){}
        void init();
        void update();
        void handleMotionEvents(android_input_buffer* inputBuffer);
        void handleKeyEvents(android_input_buffer* inputBuffer);
        bool getScreenDown(unsigned int index);
        bool getScreenPress(unsigned int index);
        bool getScreenUp(unsigned int index);
        bool getScreenClick(unsigned int index);

    };
}