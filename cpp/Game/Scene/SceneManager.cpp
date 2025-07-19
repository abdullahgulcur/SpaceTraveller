#include "pch.h"
#include "SceneManager.h"

namespace Game {

	void SceneManager::init() {

        //sceneType = SceneType::TERRAIN_TEST;
        sceneType = SceneType::UNIVERSE;
        //sceneType = SceneType::PLANET_TEST;

        universeScene.init();
        terrainSceneTest.init();

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.start(); break;
        }
        case SceneType::TERRAIN_TEST: {
            terrainSceneTest.start(); break;
        }
        case SceneType::PLANET_TEST: {

#if PLATFORM == WIN
            planetSceneTest.start(); break;
#endif

        }
        }

	}

    void SceneManager::update(float dt) {

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.update(dt); break;
        }
        case SceneType::TERRAIN_TEST: {
            terrainSceneTest.update(dt); break;
        }
        case SceneType::PLANET_TEST: {

#if PLATFORM == WIN
            planetSceneTest.update(dt); break;
#endif

        }
        }
    }


}