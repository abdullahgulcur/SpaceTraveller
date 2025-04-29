#include "pch.h"
#include "AppSurface.h"

namespace Engine {

    void AppSurface::init() {

#ifdef PLATFORM "ANDROID"
        eglContext.init();
#elif PLATFORM "WIN"

#endif
    }

    void AppSurface::update() {
#ifdef PLATFORM "ANDROID"
        eglContext.swapBuffers();
        eglContext.updateRenderArea();
#elif PLATFORM "WIN"

#endif
    }

    float AppSurface::getAspectRatio(){
#ifdef PLATFORM "ANDROID"
        return (float)eglContext.width / eglContext.height;
#elif PLATFORM "WIN"

#endif
    }

    unsigned int AppSurface::getWidth(){
#ifdef PLATFORM "ANDROID"
        return eglContext.width;
#elif PLATFORM "WIN"

#endif
    }

    unsigned int AppSurface::getHeight(){
#ifdef PLATFORM "ANDROID"
        return eglContext.height;
#elif PLATFORM "WIN"

#endif
    }

}