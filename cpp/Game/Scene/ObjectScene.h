#pragma once

#include "Core.h"

#include "glm.hpp"

namespace Game {

    class ObjectScene {
    private:

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;

        Engine::MeshData::MeshData meshData;

        Engine::Shader::SimpleShaderProgram shaderProgram;

        unsigned int textureId;

        unsigned int vao;
        std::vector<glm::mat4> models;
        unsigned int instanceBuffer;

    public:

        ObjectScene() {}
        ~ObjectScene() {}

        void init();
        void update(float dt);
    };
}