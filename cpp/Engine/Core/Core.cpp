#include "pch.h"
#include "core.h"

#include "GraphicsApi.h"

namespace Engine {

    Core* Core::instance;

    void Core::init() {

        eglContext.init();
        input.init();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void Core::update() {

        systemTimer.update();
        eglContext.swapBuffers();
        eglContext.updateRenderArea();
        input.handleInput();
    }

    Core* Core::getInstance() {
        if (!instance)
            instance = new Core;
        return instance;
    }

}