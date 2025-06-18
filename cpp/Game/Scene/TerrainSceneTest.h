#pragma once

#include "CameraController.h"

namespace Game {

    class TerrainSceneTest {
    private:

        CameraController cameraCtrl;

    public:

        TerrainSceneTest() {}
        ~TerrainSceneTest() {}

        void init();
        void start();
        void update(float dt);

    };
}