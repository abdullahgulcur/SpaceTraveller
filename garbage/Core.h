#pragma once

#include "AppSurface.h"
#include "Input.h"
#include "Timer.h"

namespace Engine {

    class Core {
    private:

        static Core* instance;

        Core() {}
        ~Core() {}

    public:

        AppSurface appSurface;
        Input input;
        Timer::SystemTimer systemTimer;

        void init();
        void update();
        static Core* getInstance();
    };
}