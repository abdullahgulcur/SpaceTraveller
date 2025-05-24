#include "pch.h"
#include "Entity.h"
#include "Vao.h"
#include "DrawCommand.h"

namespace Engine {

    namespace Entity {

        void init(EntityParticle& entityParticle, unsigned int vertexBuffer, unsigned int instanceBuffer) {

            Engine::Vao::createParticleMeshVao(entityParticle.vao, vertexBuffer, instanceBuffer);
            Engine::Shader::createShaderParticle(entityParticle.shaderProgram);
        }

        //void update(EntityParticle& entityParticle, unsigned int particleInstanceBuffer, glm::mat4 projectionView, glm::vec3 cameraRight, glm::vec3 cameraUp, ParticleSystem::ParticleSmoke& smoke) {
        //    
        //    ParticleSystem::ParticleGPUData gpuData[4096];
        //    fillInstanceData(smoke, gpuData);

        //    Engine::Shader::updateUniforms(entityParticle.shaderProgram, projectionView, cameraRight, cameraUp);
        //    Engine::DrawCommand::drawQuadsInstanced(entityParticle.vao, smoke.particleCount, particleInstanceBuffer, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

        //}

    }

}
