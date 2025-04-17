#pragma once

#include "Core.h"
//#include "Scene.h"
//#include "ParticleScene.h"
#include "UniverseScene.h"

namespace Game {

    class Game {
    private:

        static Game* instance;

        UniverseScene scene;

    public:

        Game() {}
        ~Game() {}

        void init();
        void update(float dt);

        static Game* getInstance();
    };
}