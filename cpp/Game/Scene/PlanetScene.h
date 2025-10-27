#pragma once

#include "CameraController.h"
#include "TerrainGeometryManager.h"

namespace Game {

    class PlanetScene {
    private:

        CameraController cameraCtrl;
        Engine::TerrainGeometryManager terrainGeometryManager;

    public:

        PlanetScene() {}
        ~PlanetScene() {}

        void init();
        void start();
        void update(float dt);

    };
}