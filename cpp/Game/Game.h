#pragma once

#include "Core.h"
#include "ObjectScene.h"
#include "ParticleScene.h"
#include "UniverseScene.h"
#include "TunnelEffectScene.h"

namespace Game {

    class Game {
    private:

        static Game* instance;

        ObjectScene scene;
//        ParticleScene scene;
        //UniverseScene scene;
        //TunnelEffectScene scene;

    public:

        Game() {}
        ~Game() {}

        void init();
        void update(float dt);

        static Game* getInstance();
    };
}