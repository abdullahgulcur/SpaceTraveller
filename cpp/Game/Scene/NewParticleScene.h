#pragma once

#include "Core.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "OrbitCameraController.h"
#include "ShaderProgram.h"

namespace Game {

    class NewParticleScene {
    private:

        Engine::ParticleSystem::ParticleSmoke particleSystem;
        unsigned int particleMeshVao;
        unsigned int particleInstanceBuffer;
        Engine::Shader::ShaderParticle shaderProgram;
        Engine::Camera::Camera camera;
        OrbitCameraController cameraCtrl;

        unsigned int gridVao;
        Engine::Shader::ShaderGrid shaderProgramGrid;
        unsigned int gridVertexCount;

    public:

        NewParticleScene() {}
        ~NewParticleScene() {}

        void init();
        void update(float dt);
    };
}