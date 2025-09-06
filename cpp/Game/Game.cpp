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

        while (!renderingContext.appClose)
            renderingContext.render();
    }


    void Game::initRenderThread() {

        //appSurface.init(); // main and rendering thread

        //input.init(&appSurface); // main thread
        //Engine::Graphics::init(); // rendering thread

        ////----------------------

        //universe.init(); // main thread
        //assetGenerator.init(); // rendering thread
        //sceneManager.init(); // main thread

        ////Engine::Gizmo::init(grid);

        //Engine::Camera::init(camera, 45.0f, appSurface.getAspectRatio()); // main thread

        //glm::ivec2 screenSize;
        //appSurface.getSize(screenSize); // main thread
        //sceneFrame.init(screenSize); // rendering thread

        renderingContext.init();
    }

    void Game::init() {

        appSurface.init(); // main and rendering thread

        input.init(&appSurface); // main thread
        Engine::Graphics::init(); // rendering thread

        //----------------------

        universe.init(); // main thread
        assetGenerator.init(); // rendering thread
        sceneManager.init(); // main thread

        //Engine::Gizmo::init(grid);

        Engine::Camera::init(camera, 45.0f, appSurface.getAspectRatio()); // main thread

        glm::ivec2 screenSize;
        appSurface.getSize(screenSize); // main thread
        sceneFrame.init(screenSize); // rendering thread
    }

    void Game::update() {

        appSurface.glfwContext.pollEvents();
        input.update();

        systemTimer.update(); // sim thread
        sceneManager.update(systemTimer.getDeltaSeconds()); // sim thread

        if (appSurface.aspectChanged()) // sim thread
            Engine::Camera::setAspect(camera, appSurface.getAspectRatio()); // sim thread

        appSurface.update(); // render thread
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}