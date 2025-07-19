#pragma once

#include "Core.h"
#include "Camera.h"
#include "SceneFrame.h"
#include "Universe.h"
#include "Gizmo.h"
#include "AssetGenerator.h"
#include "SceneManager.h"
#include "TerrainGeometryManager.h"

namespace Game {

    class Game {
    private:

        static Game* instance;
        Engine::Gizmo::Grid grid;

    public:

        Universe universe;
        AssetGenerator assetGenerator;
        SceneManager sceneManager;
        SceneFrame sceneFrame;
        Engine::Camera::Camera camera;

        Engine::TerrainGeometryManager terrainGeometryManager; // burda olmasi cok mantikli gelmedi, geciciydi sanirim

        Game() {}
        ~Game() {}

        void init();
        void update(float dt);

        static Game* getInstance();
    };
}