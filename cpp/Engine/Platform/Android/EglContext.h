#pragma once

#include <EGL/egl.h>

struct android_app;

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

        void init(android_app *app_);
        void updateRenderArea();
        void swapBuffers();
    };
}