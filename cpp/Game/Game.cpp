#include "pch.h"
#include "Game.h"
#include "Graphics.h"

// game::init fonksiyonunun threadlere ayrilmasi
// rendering context in buffer lar implementasyonu
// rendering update loop
// android implementasyonu

namespace Game {

    Game* Game::instance;

    void Game::open() {

        Game::init();

        std::thread renderThread(&Game::threadRendering, this);

        while (!appSurface.glfwContext.shouldClose())
            Game::update();

        renderingContext.appClose = true;
        renderThread.join();
    }

    void Game::threadRendering() {

        Game::initRenderThread();

        while (!renderingContext.appClose) {
            renderingContext.update();
            appSurface.update();
        }
    }


    void Game::initRenderThread() {

        appSurface.glfwContext.makeContextCurrent();
        Engine::Graphics::init();

        assetGenerator.initRenderObjects();

        //glm::ivec2 screenSize;
        //appSurface.getSize(screenSize);
        //sceneFrame.init(screenSize);

        renderingContext.init();
    }

    void Game::init() {

        appSurface.init();
        input.init(&appSurface);
        universe.init();
        assetGenerator.init();
        sceneManager.init();
        Engine::Camera::init(camera, 45.0f, appSurface.getAspectRatio());
    }

    void Game::update() {

        appSurface.glfwContext.pollEvents();
        input.update();
        systemTimer.update();

        // -------- sequence is important --------
        renderingContext.setSimulationBufferIndex();
        sceneManager.update(systemTimer.getDeltaSeconds());
        renderingContext.setLastFilledBufferIndex();
        // ---------------------------------------

        if (appSurface.aspectChanged())
            Engine::Camera::setAspect(camera, appSurface.getAspectRatio());
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}