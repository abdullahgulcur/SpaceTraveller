#pragma once

#if PLATFORM == ANDROID
#include "EglContext.h"
#elif PLATFORM == WIN
#include "GlfwContext.h"
#endif

namespace Engine {

    class AppSurface {
    private:

    public:

#if PLATFORM == ANDROID
        EglContext eglContext;
#elif PLATFORM == WIN
        GlfwContext glfwContext;
#endif

        AppSurface() {}
        ~AppSurface() {}

        void init();
        void update();
        unsigned int getWidth();
        unsigned int getHeight();
        float getAspectRatio();
    };
}