#pragma once

#include <EGL/egl.h>

namespace Engine {

    class EglContext {
    private:

    public:

        EGLDisplay display_;
        EGLSurface surface_;
        EGLContext context_;
        EGLint width_;
        EGLint height_;

        EglContext();
        ~EglContext() {}

        void init();
        void updateRenderArea();
        void swapBuffers();
    };
}