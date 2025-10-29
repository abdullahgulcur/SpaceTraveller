#pragma once

#include "AppSurface.h"
#include "Input.h"
#include "Timer.h"

#include "Camera.h"
#include "SceneFrame.h"
#include "RenderingContext.h"
#include "AssetGenerator.h"
#include "SceneManager.h"

namespace Game {

    class Game {
    private:


        static Game* instance;

    public:

        Engine::AppSurface appSurface;
        Engine::Input input;
        Timer::SystemTimer systemTimer;

        AssetGenerator assetGenerator;
        SceneManager sceneManager;
        SceneFrame sceneFrame;
        Engine::Camera::Camera camera;

        RenderingContext renderingContext;
        std::thread renderThread;

        bool shouldOpen = false;

        Game() {}
        ~Game() {}
        void threadRendering();
        void init();
        void update();
        void shutDown();
        static Game* getInstance();
    };
}