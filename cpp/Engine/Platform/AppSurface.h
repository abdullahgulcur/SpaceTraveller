#pragma once

#ifdef PLATFORM "ANDROID"
#include "EglContext.h"
#elif PLATFORM "WIN"

#endif

namespace Engine {

    class AppSurface {
    private:

    public:

#ifdef PLATFORM "ANDROID"
        EglContext eglContext;
#elif PLATFORM "WIN"

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