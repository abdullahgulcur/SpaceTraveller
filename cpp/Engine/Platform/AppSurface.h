#pragma once
#include "glm.hpp"
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
        float getAspectRatio();
        bool aspectChanged();
        unsigned int getWidth();
        unsigned int getHeight();
        void getSize(glm::ivec2& size);
        void getScreenSpaceCoordinate(glm::ivec2& screenSpaceCoordinate, glm::vec2 normalizedCoordinate);
    };
}