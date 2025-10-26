#pragma once

#include "AppSurface.h"
#include "Input.h"
#include "Timer.h"

#include "Camera.h"
#include "SceneFrame.h"
#include "Universe.h"
#include "RenderingContext.h"
//#include "Gizmo.h"
#include "AssetGenerator.h"
#include "SceneManager.h"
#include "TerrainGeometryManager.h"

namespace Game {

    class Game {
    private:

        std::thread renderThread;

        static Game* instance;
        //Engine::Gizmo::Grid grid;

    public:


        Engine::AppSurface appSurface;
        Engine::Input input;
        Timer::SystemTimer systemTimer;

        Universe universe;
        AssetGenerator assetGenerator;
        SceneManager sceneManager;
        SceneFrame sceneFrame;
        Engine::Camera::Camera camera;

        Engine::TerrainGeometryManager terrainGeometryManager; // burda olmasi cok mantikli gelmedi, geciciydi sanirim

        RenderingContext renderingContext;

        bool shouldOpen = false;

        Game() {}
        ~Game() {}
        //void open();
        void threadRendering();
        void init();
        void update();
        static Game* getInstance();
    };
}