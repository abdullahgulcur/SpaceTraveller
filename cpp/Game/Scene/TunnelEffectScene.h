#pragma once

#include "Core.h"
#include "ParticleSystem.h"

#include "glm.hpp"

namespace Game {

    class TunnelEffectScene {
    private:

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;
        Engine::ParticleSystem::ParticleTunnelEffect particleSystem;

        unsigned int particleMeshVao;
        Engine::VertexBuffer::VertexBuffer particleInstanceBuffer;
        Engine::ShaderProgram shaderProgram;

    public:

        TunnelEffectScene() {}
        ~TunnelEffectScene() {}

        void init();
        void update(float dt);
    };
}