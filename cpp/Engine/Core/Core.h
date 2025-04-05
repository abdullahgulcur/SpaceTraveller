#pragma once

#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "EglContext.h"
#include "AssetManager.h"
#include "Input.h"

namespace Engine {

    class Core {
    private:

        //float y = 0;
        //int dir = -1;

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;

        Vao::Vao vao;

        std::vector<glm::mat4> models;

        VertexBuffer::VertexBuffer instanceBuffer;

        static Core* instance;

        Core() {}
        ~Core() {}

    public:

        android_app *app_;

        EglContext eglContext;
        AssetManager assetManager;
        Input input;

        void init(android_app *app_);
        void update();
        static Core* getInstance();
    };
}