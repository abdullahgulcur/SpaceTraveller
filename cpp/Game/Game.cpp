#include "pch.h"
#include "Game.h"

namespace Game {

    Game* Game::instance;

    void Game::init() {

        universe.init();
        assetGenerator.init();
        sceneManager.init();

        Engine::Gizmo::init(grid);

        Engine::Core* core = Engine::Core::getInstance();

        Engine::Camera::init(camera, 45.0f, core->appSurface.getAspectRatio());

        glm::ivec2 screenSize;
        core->appSurface.getSize(screenSize);
        sceneFrame.init(screenSize);
        //terrainGeometryManager.init(camera.position); // burda olmasi cok mantikli gelmedi, geciciydi sanirim
    }

    void Game::update(float dt) {

        //terrainGeometryManager.update(camera.position); // burda olmasi cok mantikli gelmedi, geciciydi sanirim

        sceneManager.update(dt);

        //Engine::Gizmo::update(grid, camera.projectionView);

        Engine::Core* core = Engine::Core::getInstance();
        if (core->appSurface.aspectChanged())
            Engine::Camera::setAspect(camera, core->appSurface.getAspectRatio());
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}