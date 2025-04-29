#pragma once

#include "AndroidApplication.h"
#include "EglContext.h"
#include "AssetManager.h"
#include "Input.h"
#include "Timer.h"

namespace Engine {

    class Core {
    private:

        static Core* instance;

        Core() {}
        ~Core() {}

    public:

        EglContext eglContext; // WindowContext !!!
        Input input;
        Timer::SystemTimer systemTimer;

        void init();
        void update();
        static Core* getInstance();
    };
}