#pragma once

#include "Core.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "CameraController.h"
#include "ShaderProgram.h"

namespace Game {

    class ParticleScene {
    private:

        Engine::ParticleSystem::ParticleSystem* particleSystem;
        unsigned int particleMeshVao;
        unsigned int particleInstanceBuffer;
        Engine::Shader::SimpleShaderProgram shaderProgram;
        Engine::Camera::Camera camera;
        CameraController cameraCtrl;

    public:

        ParticleScene() {}
        ~ParticleScene() {}

        void init();
        void update(float dt);
    };
}