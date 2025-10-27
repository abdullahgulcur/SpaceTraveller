#include "pch.h"
#include "SceneManager.h"

namespace Game {

	void SceneManager::init() {

        //sceneType = SceneType::TERRAIN_TEST;
        sceneType = SceneType::UNIVERSE;
        //sceneType = SceneType::PLANET_TEST;
        //sceneType = SceneType::SUN_TEST;

        universeScene.init();
//        terrainSceneTest.init();

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.start(); break;
        }
        case SceneType::PLANET: {
            planetScene.start(); break;
        }
//        case SceneType::TERRAIN_TEST: {
//            terrainSceneTest.start(); break;
//        }
//#if PLATFORM == WIN
//        case SceneType::PLANET_TEST: {
//            planetSceneTest.start(); break;
//        }
//        case SceneType::SUN_TEST: {
//            sunSceneTest.start(); break;
//        }
//#endif

        }

	}

    void SceneManager::update(float dt) {

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.update(dt); break;
        }
        case SceneType::PLANET: {
            planetScene.update(dt); break;
        }
//        case SceneType::TERRAIN_TEST: {
//            terrainSceneTest.update(dt); break;
//        }
//#if PLATFORM == WIN
//        case SceneType::PLANET_TEST: {
//            planetSceneTest.update(dt); break;
//        }
//        case SceneType::SUN_TEST: {
//            sunSceneTest.update(dt); break;
//        }
//#endif

        }
    }


}