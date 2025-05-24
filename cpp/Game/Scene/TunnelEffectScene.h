#pragma once

#include "Core.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "CameraController.h"
#include "ShaderProgram.h"
namespace Game {

    class TunnelEffectScene {
    private:

    public:

        TunnelEffectScene() {}
        ~TunnelEffectScene() {}

        void init();
        void start();
        void update(float dt);
    };
}