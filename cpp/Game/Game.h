#pragma once

#include "Core.h"
#include "PlanetScene.h"
#include "NewParticleScene.h"

//#include "ObjectScene.h"
//#include "ParticleScene.h"
//#include "UniverseScene.h"
//#include "TunnelEffectScene.h"

namespace Game {

    class Game {
    private:

        static Game* instance;

        NewParticleScene scene;
        //PlanetScene scene;

        //ObjectScene scene;
        //ParticleScene scene;
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