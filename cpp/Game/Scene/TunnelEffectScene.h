#pragma once

#include "Core.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "CameraController.h"
#include "ShaderProgram.h"
namespace Game {

    class TunnelEffectScene {
    private:

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;
        Engine::ParticleSystem::ParticleTunnelEffect particleSystem;

        unsigned int particleMeshVao;
        unsigned int particleInstanceBuffer;
        Engine::Shader::SimpleShaderProgram shaderProgram;
        Engine::Camera::Camera camera;
        CameraController cameraCtrl;

    public:

        TunnelEffectScene() {}
        ~TunnelEffectScene() {}

        void init();
        void update(float dt);
    };
}