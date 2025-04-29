#pragma once

namespace Game {

    class CameraController {
    private:

        float horizontalAngle = 0;
        float targetHorizontalAngle = 0;

    public:


        CameraController() {}

        void init(Engine::Camera::Camera& camera);
        void update(Engine::Camera::Camera& camera, float dt);

    };
}