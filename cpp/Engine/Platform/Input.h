#pragma once
#include "glm.hpp"

namespace Engine {

    class Input {
    private:

    public:

        glm::ivec2 pointerPosition;
        glm::ivec2 pointerDelta;

        Input(){}
        ~Input(){}
        void init();
        void update();
    };
}