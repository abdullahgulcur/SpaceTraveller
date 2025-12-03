#pragma once

#include "AppSurface.h"
#include "Input.h"
#include "Timer.h"

#include "Camera.h"
#include "SceneFrame.h"
#include "RenderingContext.h"
#include "AssetGenerator.h"
#include "SceneManager.h"
#include "AsyncTextureGenerator.h"

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
        //AsyncTextureGenerator asyncTextureGenerator;
        std::thread renderThread;
        std::thread asyncTextureGeneratorThread;

        bool shouldOpen = false;

        //bool temp = false;

        Game() {}
        ~Game() {}
        void threadRendering();
        //void threadAsyncTextureGenerator();
        void init();
        void update();
        void shutDown();
        static Game* getInstance();
    };
}