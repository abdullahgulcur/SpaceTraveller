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

    bool AppSurface::aspectChanged() {
#if PLATFORM == ANDROID
        return eglContext.aspectChanged;
#elif PLATFORM == WIN
        return false;
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

    void AppSurface::getSize(glm::u16vec2& size) {
        size = glm::u16vec2(AppSurface::getWidth(), AppSurface::getHeight());
    }

    void AppSurface::getScreenSpaceCoordinate(glm::u16vec2& screenSpaceCoordinate, glm::vec2 normalizedCoordinate) {
        glm::u16vec2 size;
        AppSurface::getSize(size);

        screenSpaceCoordinate.x = (normalizedCoordinate.x + 1.0f) * 0.5f * size.x;
        //screenSpaceCoordinate.y = (normalizedCoordinate.y + 1.0f) * 0.5f * size.y;
        screenSpaceCoordinate.y = (1.0f - normalizedCoordinate.y) * 0.5f * size.y;
    }

}