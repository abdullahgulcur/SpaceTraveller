#pragma once

#include "OrbitCameraController.h"

namespace Game {

    class UniverseScene {
    private:

        OrbitCameraController cameraCtrl;
        unsigned int instanceBufferSolarSystems;
        unsigned int vaoBillboardSolarSystems;

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void start();
        void update(float dt);
    };
}

//different scenes (state changes), shared data in same class