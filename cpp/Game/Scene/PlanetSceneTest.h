#pragma once

#include "OrbitCameraController.h"

namespace Game {

    class PlanetSceneTest {
    private:

        glm::vec3 waterColor { 0.1f, 0.3f, 0.9f };
        float amountSea = 0.5f;

        OrbitCameraController cameraCtrl;

    public:

        PlanetSceneTest() {}
        ~PlanetSceneTest() {}

        void init();
        void start();
        void update(float dt);

    };
}