#pragma once

#include "OrbitCameraController.h"

namespace Game {

    class PlanetSceneTest {
    private:

        glm::vec3 waterColor{ 0 / 255.f, 10 / 255.f, 39 / 255.f };
        glm::vec3 continentalShelfColor{ 0 / 255.f, 15 / 255.f, 131 / 255.f };
        float amountSea = 0.70f;
        float continentalShelf = 0.05f;
        float landColorOverlay = 2.45f;
        float landColorPower = 2.62f;
        float surfaceTopologyScale = 0.05f;
        float landColorBlendScale = 0.5f;

        glm::vec3 landColor0{ 32 / 255.f, 45 / 255.f, 18 / 255.f };
        glm::vec3 landColor1{ 93 / 255.f, 76 / 255.f, 31 / 255.f };


        OrbitCameraController cameraCtrl;

    public:

        PlanetSceneTest() {}
        ~PlanetSceneTest() {}

        void init();
        void start();
        void update(float dt);

    };
}