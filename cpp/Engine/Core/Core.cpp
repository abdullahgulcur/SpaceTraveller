#include "pch.h"
#include "core.h"

#include "GraphicsApi.h" // should not be here

namespace Engine {

    Core* Core::instance;

    void Core::init() {

        appSurface.init();
        input.init();

        // should not be here ---------
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        //  ---------  ---------
    }

    void Core::update() {

        systemTimer.update();
        appSurface.update();
        input.update();
    }

    Core* Core::getInstance() {
        if (!instance)
            instance = new Core;
        return instance;
    }

}