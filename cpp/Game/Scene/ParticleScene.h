#pragma once

#include "Core.h"
#include "ParticleSystem.h"

#include "glm.hpp"

namespace Game {

    class ParticleScene {
    private:

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;
        Engine::ParticleSystem::ParticleSystem* particleSystem;

        unsigned int particleMeshVao;
        unsigned int particleInstanceBuffer;
        Engine::Shader::SimpleShaderProgram shaderProgram;

    public:

        ParticleScene() {}
        ~ParticleScene() {}

        void init();
        void update(float dt);
    };
}