#pragma once

#include "Core.h"

#include "glm.hpp"

namespace Game {

    class UniverseScene {
    private:

        float horizontalPos = 0;
        float targetHorizontalPos = 0;


        unsigned int galaxyMeshVao;
        unsigned int galaxyInstanceBuffer;
        Engine::Shader::SimpleShaderProgram shaderProgram;
        unsigned int texture2D;

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void update(float dt);
    };
}