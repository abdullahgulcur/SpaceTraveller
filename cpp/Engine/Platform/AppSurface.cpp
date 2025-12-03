#include "pch.h"
#include "AppSurface.h"

namespace Engine {

    void AppSurface::init() {

        glContext.init();
    }

    void AppSurface::swapBuffers() {

        glContext.swapBuffers();
    }

    void AppSurface::checkScreenSize() {

        glContext.checkScreenSize();
    }

    float AppSurface::getAspectRatio(){

        return glContext.getAspectRatio();
    }

    bool AppSurface::aspectChanged() {

        return glContext.getAspectChanged();
    }

    void AppSurface::getScreenSize(glm::ivec2& size) {

        glContext.getScreenSize(size);
    }

    void AppSurface::getScreenSpaceCoordinate(glm::ivec2& screenSpaceCoordinate, glm::vec2 normalizedCoordinate) {
        glm::ivec2 size;
        AppSurface::getScreenSize(size);
        screenSpaceCoordinate.x = (normalizedCoordinate.x + 1.0f) * 0.5f * size.x;
        //screenSpaceCoordinate.y = (normalizedCoordinate.y + 1.0f) * 0.5f * size.y;
        screenSpaceCoordinate.y = (1.0f - normalizedCoordinate.y) * 0.5f * size.y;
    }

    void AppSurface::makeRenderingContextCurrent() {

        glContext.makeContextCurrent();
    }

    //void AppSurface::makeAsyncTextureGeneratorContextCurrent() {

    //    glContext.makeContextCurrent(glContext.glfwAsyncTextureGeneratorWindow);
    //}

#if PLATFORM == WIN
    void AppSurface::pollEvents() {
        glContext.pollEvents();
    }

    bool AppSurface::shouldClose() {
        return glContext.shouldClose();
    }
#endif

}