#pragma once

#include "Core.h"

#include "glm.hpp"

namespace Game {

    class UniverseScene {
    private:

        Engine::Vao::Vao galaxyMeshVao;
        Engine::VertexBuffer::VertexBuffer galaxyInstanceBuffer;
        Engine::ShaderProgram shaderProgram;
        Engine::Texture2D texture2D;

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void update(float dt);
    };
}