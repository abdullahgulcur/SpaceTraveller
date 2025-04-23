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
        Engine::Shader::ShaderProgramParticle shaderProgram;
        Engine::Texture2D texture2D;

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void update(float dt);
    };
}