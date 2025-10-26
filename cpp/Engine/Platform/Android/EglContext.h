#pragma once

#include <EGL/egl.h>

namespace Engine {

    class EglContext {
    private:

    public:

        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        EGLConfig config;
        EGLint width;
        EGLint height;
        bool aspectChanged = false;

        EglContext() {}
        ~EglContext() {}

        void init();
        void updateRenderArea();
        void swapBuffers();
        void makeContextCurrent();


    };
}