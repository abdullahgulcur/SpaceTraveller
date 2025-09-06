#pragma once

#include "OrbitCameraController.h"
#include "Universe.h"

namespace Game {

    class SunSceneTest {
    private:

        //std::vector<PlanetColors> planetColors;

        glm::vec3 color0{ 1.f, 1.f, 0.f };
        glm::vec3 color1{ 1.f, 0.f, 0.f };
        glm::vec3 color2{ 0.f, 0.f, 0.f };
        glm::vec3 color3{ 1.f, 0.5f, 0.f };
        float colorOverlay0 = 1.f;
        float colorOverlay1 = 0.93f;
        float colorPower0 = 1.f;
        float colorPower1 = 2.f;
        float noiseScale = 1.f;
        int noiseTexIndex = 0;
        unsigned int texArray;
        float fresnelPower = 0.7f;
        float fresnelScale = 1.f;
        float fresnelBias = 1.f;

        OrbitCameraController cameraCtrl;

    public:

        SunSceneTest() {}
        ~SunSceneTest() {}

        void init();
        //void parsePlanetColors(std::vector<PlanetColors>& planetColors, const std::vector<unsigned char>& buffer);
        void start();
        void update(float dt);

    };
}