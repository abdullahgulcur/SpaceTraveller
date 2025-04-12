#include "pch.h"
#include "core.h"

#include <GLES3/gl32.h> // will be removed

namespace Engine {

    Core* Core::instance;

    void Core::init(android_app *app_) {

        this->app_ = app_;
        app_->userData = this;

        eglContext.init(this->app_);
        input.init(app_);

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