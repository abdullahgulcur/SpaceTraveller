#pragma once

#include "glm.hpp"
#include "Timer.h"
#include "Camera.h"

namespace Game {

    struct CameraState {
        Engine::Camera::CameraTransform cameraTransform;
        float startTime;
    };

    class TranslateCameraController {

    private:

    public:

        Engine::Camera::CameraTransform currentTransform;

        StaticArray<Engine::Camera::CameraTransform, 4> transformQueue;
        StaticArray<float, 4> durationQueue;

        Timer::StopWatch stopWatch;
        bool isUpdating = false;
        /*float accelerationPeriod = 1.5f;
        float movePeriod = 1.5f;
        float cameraOrientPeriod = 1.5f;*/

        TranslateCameraController() {}

        void init();
        void update(float dt);

        float lerpAngle(float a, float b, float t);
        void push(Engine::Camera::CameraTransform& cameraTransform, float timeStamp);
        void cleanQueue();

        glm::vec3 getPosition() const;
        glm::vec3 getForward() const;
        //void push(Engine::Camera::CameraTransform cameraTransform, float duration);
    };
}