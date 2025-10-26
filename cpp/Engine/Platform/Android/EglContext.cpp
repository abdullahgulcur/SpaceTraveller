#include "pch.h"
#include "EglContext.h"
#include "AndroidApplication.h"

namespace Engine {

    void EglContext::init() {

        // Choose your render attributes
        constexpr EGLint attribs[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_DEPTH_SIZE, 24,
                EGL_NONE
        };

        // The default display is probably what you want on Android
        auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(display, nullptr, nullptr);

        // figure out how many configs there are
        EGLint numConfigs;
        eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

        // get the list of configurations
        std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
        eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

        // Find a config we like.
        // Could likely just grab the first if we don't care about anything else in the config.
        // Otherwise hook in your own heuristic
        auto config = *std::find_if(
                supportedConfigs.get(),
                supportedConfigs.get() + numConfigs,
                [&display](const EGLConfig &config) {
                    EGLint red, green, blue, depth;
                    if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                        && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                        && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                        && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                        //aout << "Found config with " << red << ", " << green << ", " << blue << ", "
                        //     << depth << std::endl;
                        return red == 8 && green == 8 && blue == 8 && depth == 24;
                    }
                    return false;
                });

        EGLint format;
        eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

        this->display = display;
        this->config = config;
    }

    void EglContext::updateRenderArea() {

        EGLint width;
        eglQuerySurface(display, surface, EGL_WIDTH, &width);

        EGLint height;
        eglQuerySurface(display, surface, EGL_HEIGHT, &height);

        if (this->width != width || this->height != height) {
            this->width = width;
            this->height = height;
            aspectChanged = true;
            return;
        }

        aspectChanged = false;
    }

    void EglContext::swapBuffers() {
        eglSwapBuffers(display, surface);
    }

    void EglContext::makeContextCurrent(){

        EGLSurface surface = eglCreateWindowSurface(display, config, AndroidApplication::application->window, nullptr);
        EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_CONTEXT_MINOR_VERSION, 2, EGL_NONE};
        EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);
        eglMakeCurrent(display, surface, surface, context);

        this->context = context;
        this->surface = surface;
    }
}