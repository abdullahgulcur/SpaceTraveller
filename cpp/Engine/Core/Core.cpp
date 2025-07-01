#include "pch.h"
#include "core.h"

#include "GraphicsApi.h" // should not be here

namespace Engine {

    Core* Core::instance;

    void Core::init() {

        appSurface.init();
        input.init();

#if PLATFORM == WIN
        glewExperimental = true;
        glewInit();
#endif

        // should not be here ---------
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        //  ---------  ---------
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