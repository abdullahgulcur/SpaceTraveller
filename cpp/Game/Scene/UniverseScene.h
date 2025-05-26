#pragma once

#include "OrbitCameraController.h"

namespace Game {

    enum class StateMovement {
        IDLE = 0,
        ACCELERATING = 1,
        MOVING = 2
    };

    class UniverseScene {
    private:

        StateMovement stateMovement;

        float accStartTime;
        float accPeriod = 1.5f;

        OrbitCameraController cameraCtrl;
        /*unsigned int instanceBufferSolarSystems;
        unsigned int vaoBillboardSolarSystems;*/

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void start();
        void update(float dt);

        void stateIdle(float dt);
        void stateAccelerating(float dt);
        void stateMoving(float dt);
    };
}

//different scenes (state changes), shared data in same class