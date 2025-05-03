#include "pch.h"
#include "AppSurface.h"

namespace Engine {

    void AppSurface::init() {

#if PLATFORM == ANDROID
        eglContext.init();
#elif PLATFORM == WIN
        glfwContext.init();
#endif
    }

    void AppSurface::update() {
#if PLATFORM == ANDROID
        eglContext.swapBuffers();
        eglContext.updateRenderArea();
#elif PLATFORM == WIN
        glfwContext.swapBuffers();
#endif
    }

    float AppSurface::getAspectRatio(){
#if PLATFORM == ANDROID
        return (float)eglContext.width / eglContext.height;
#elif PLATFORM == WIN
        return (float)glfwContext.mode->width / glfwContext.mode->height;
#endif
    }

    unsigned int AppSurface::getWidth(){
#if PLATFORM == ANDROID
        return eglContext.width;
#elif PLATFORM == WIN
        return glfwContext.mode->width;
#endif
    }

    unsigned int AppSurface::getHeight(){
#if PLATFORM == ANDROID
        return eglContext.height;
#elif PLATFORM == WIN
        return glfwContext.mode->height;
#endif
    }

}