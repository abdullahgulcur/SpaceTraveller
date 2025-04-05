#pragma once

#include "Core.h"

#include "glm.hpp"

namespace Game {

    class Scene {
    private:

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;

        Engine::Vao::Vao vao;
        std::vector<glm::mat4> models;
        Engine::VertexBuffer::VertexBuffer instanceBuffer;

    public:

        Scene() {}
        ~Scene() {}

        void init();
        void update();
    };
}