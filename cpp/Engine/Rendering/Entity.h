#pragma once

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "ParticleSystem.h"

namespace Engine {

    namespace Entity {

        struct EntityParticle {
            unsigned int vao;
            Engine::Shader::ShaderParticle shaderProgram;
        };

        void init(EntityParticle& entityParticle, unsigned int vertexBuffer, unsigned int instanceBuffer);
        //void update(EntityParticle& entityParticle, unsigned int particleInstanceBuffer, glm::mat4 projectionView, glm::vec3 cameraRight, glm::vec3 cameraUp, ParticleSystem::ParticleSmoke& smoke);

    }

}
