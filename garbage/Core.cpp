#include "pch.h"
#include "core.h"
#include "Graphics.h"

namespace Engine {

    Core* Core::instance;

    void Core::init() {

        appSurface.init(); // rendering thread

        input.init();
        Graphics::init(); // rendering thread
    }

    void Core::update() {

#if PLATFORM == WIN
        appSurface.glfwContext.pollEvents(); // rendering thread
#endif
        input.update();
        systemTimer.update();
    }

    Core* Core::getInstance() {
        if (!instance)
            instance = new Core;
        return instance;
    }

}