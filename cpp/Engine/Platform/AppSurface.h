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

#if PLATFORM == ANDROID
        EglContext glContext;
#elif PLATFORM == WIN
        GlfwContext glContext;
#endif

    public:

        friend class Input;

        AppSurface() {}
        ~AppSurface() {}
        void init();
        void swapBuffers();
        void checkScreenSize();
        //void update();
        float getAspectRatio();
        bool aspectChanged();
        void getScreenSize(glm::ivec2& size);
        void getScreenSpaceCoordinate(glm::ivec2& screenSpaceCoordinate, glm::vec2 normalizedCoordinate);
        void makeRenderingContextCurrent();
#if PLATFORM == WIN
        void pollEvents();
        bool shouldClose();
#endif
    };
}