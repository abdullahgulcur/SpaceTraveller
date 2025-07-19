#include "pch.h"
#include "core.h"
#include "Graphics.h"

namespace Engine {

    Core* Core::instance;

    void Core::init() {

        appSurface.init();
        input.init();
        Graphics::init();
    }

    void Core::update() {

#if PLATFORM == WIN
        appSurface.glfwContext.pollEvents();
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