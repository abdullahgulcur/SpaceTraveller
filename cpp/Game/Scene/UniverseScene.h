#pragma once

#include "OrbitCameraController.h"
#include "CameraController.h"
#include "TranslateCameraController.h"
#include "Timer.h"

namespace Game {

    enum class StateMovement {
        UNIVERSE = 0,
        ACCELERATING = 1,
        MOVING = 2,
        SLOWING = 3,
        SOLAR_SYSTEM = 4,
        CAMERA_ORIENT = 5
    };

    enum class StateCameraMovement {
        IDLE = 0,
        MOVE = 1,
    };

    class UniverseScene {
    private:

        //glm::vec3 previousCameraPosition;
        //float getCameraSpeed(float dt);

        //StateMovement stateMovement;

        //float stopwatchStartTime;
        //float accPeriod = 1.5f;
        //float movePeriod = 1.5f;
        //float cameraOrientPeriod = 1.f;

        //glm::vec3 cameraPosition;
        //glm::vec3 targetCameraPosition;

        CameraController cameraCtrl;
        TranslateCameraController translateCameraCtrl;

        StateCameraMovement stateCameraMovement;

        //Engine::Timer::StopWatch stopWatch;

        //OrbitCameraController cameraCtrl;
        /*unsigned int instanceBufferSolarSystems;
        unsigned int vaoBillboardSolarSystems;*/

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void start();
        void update(float dt);

        void stateUniverse(float dt);
        void stateAccelerating(float dt);
        void stateMoving(float dt);
        void stateSlowing(float dt);
        void stateSolarSystem(float dt);
        void cameraOrient(float dt);

        //void startStopWatch();
        //float getDuration();
    };
}

//different scenes (state changes), shared data in same class