#include "pch.h"
#include "Game.h"
#include "Graphics.h"

namespace Game {

    Game* Game::instance;

    void Game::init() {

        shouldOpen = true;
        appSurface.init();
        renderThread = std::thread(&Game::threadRendering, this);
        input.init(&appSurface);
        assetGenerator.init();
        Engine::Camera::init(camera, 45.0f, appSurface.getAspectRatio());
        sceneManager.init();
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
            appSurface.checkScreenSize();
        }
    }

    void Game::update() {

        input.update();
        systemTimer.update();
        sceneManager.update(systemTimer.getDeltaSeconds());
        if (appSurface.aspectChanged())
            Engine::Camera::setAspect(camera, appSurface.getAspectRatio());
    }

    void Game::shutDown() {
        renderThread.join();
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}