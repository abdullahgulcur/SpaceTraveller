#pragma once

#include "UniverseScene.h"
#include "TerrainSceneTest.h"
#if PLATFORM == WIN
#include "PlanetSceneTest.h"
#include "SunSceneTest.h"
#endif

namespace Game {

	enum class SceneType {
		UNIVERSE = 0,
		TERRAIN_TEST = 1,
		PLANET_TEST = 2,
		SUN_TEST = 3
	};

	class SceneManager {

	private:
	public:

		UniverseScene universeScene;
		TerrainSceneTest terrainSceneTest;
#if PLATFORM == WIN
		PlanetSceneTest planetSceneTest;
		SunSceneTest sunSceneTest;
#endif
		SceneType sceneType;

		SceneManager() {}
		~SceneManager() {}
		void init();
		void update(float dt);

	};
}