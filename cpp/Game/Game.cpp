#include "pch.h"
#include "Game.h"
#include "Graphics.h"


namespace Game {

    Game* Game::instance;

    void Game::init() {

        shouldOpen = true;
        appSurface.init();
        input.init(&appSurface);
        universe.init();
        assetGenerator.init();
        sceneManager.init();
        Engine::Camera::init(camera, 45.0f, appSurface.getAspectRatio());
        renderThread = std::thread(&Game::threadRendering, this);
    }

    void Game::threadRendering() {

        appSurface.makeRenderingContextCurrent();
        Engine::Graphics::init();
        assetGenerator.initRenderObjects();

        //glm::ivec2 screenSize;
        //appSurface.getSize(screenSize);
        //sceneFrame.init(screenSize);

        renderingContext.init();

        while (shouldOpen) {
            renderingContext.update();
            appSurface.swapBuffers();
        }
    }

    void Game::update() {

#if PLATFORM == WIN
        if (appSurface.shouldClose())
            shouldOpen = false;
#endif
        if (!shouldOpen) {
            renderThread.join();
            return;
        }

#if PLATFORM == WIN
        appSurface.pollEvents();
#endif

        input.update();
        systemTimer.update();

        // -------- sequence is important --------
        renderingContext.setSimulationBufferIndex();
        sceneManager.update(systemTimer.getDeltaSeconds());
        renderingContext.setLastFilledBufferIndex();
        // ---------------------------------------

        appSurface.checkScreenSize();
        if (appSurface.aspectChanged())
            Engine::Camera::setAspect(camera, appSurface.getAspectRatio());
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}