#pragma once

#include <game-activity/native_app_glue/android_native_app_glue.h>

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

        android_app *app_;

        EglContext eglContext;
        AssetManager assetManager;
        Input input;
        Timer::SystemTimer systemTimer;

        void init(android_app *app_);
        void update();
        static Core* getInstance();
    };
}