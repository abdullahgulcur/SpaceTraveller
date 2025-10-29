#pragma once

#include <EGL/egl.h>
#include "glm.hpp"

namespace Engine {

    class EglContext {
    private:

        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        EGLConfig config;
        EGLint width;
        EGLint height;
        bool aspectChanged = false;
        std::mutex mtx;
    public:

        EglContext() {}
        ~EglContext() {}

        void init();
        void checkScreenSize();
        void swapBuffers();
        void makeContextCurrent();
        float getAspectRatio();
        void getScreenSize(glm::ivec2& size);
        bool getAspectChanged();

    };
}