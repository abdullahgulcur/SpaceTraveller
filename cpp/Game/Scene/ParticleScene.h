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

        Engine::Vao::Vao particleMeshVao;
        Engine::VertexBuffer::VertexBuffer particleInstanceBuffer;
        Engine::ShaderProgram shaderProgram;

    public:

        ParticleScene() {}
        ~ParticleScene() {}

        void init();
        void update(float dt);
    };
}