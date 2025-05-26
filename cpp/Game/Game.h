#pragma once

#include "Core.h"
#include "Camera.h"

//#include "PlanetScene.h"
//#include "NewParticleScene.h"
#include "UniverseScene.h"

#include "Universe.h"
#include "ShaderProgram.h"
#include "Gizmo.h"

//#include "ObjectScene.h"
//#include "ParticleScene.h"

//#include "TunnelEffectScene.h"

namespace Game {

    enum class SceneType {
        UNIVERSE = 0,
        TUNNEL_EFFECT = 1,
        SOLAR_SYSTEM = 2,
        PLANET_ATMOSPHERE = 3,
        PLANET_SURFACE = 4
    };

    class Game {
    private:

        static Game* instance;

        UniverseScene universeScene;
        //NewParticleScene scene;
        //PlanetScene scene;

        //ObjectScene scene;
        //ParticleScene scene;
        
        

        Engine::Gizmo::Grid grid;

    public:

        //TunnelEffectScene tunnelEffectScene;

        Universe universe;

        Engine::ParticleSystem::ParticleTunnel<1024> particleSystem;
        Engine::ParticleSystem::ParticleSolarSystems<256> particleSolarSystems;


        Engine::Camera::Camera camera;
        Engine::Shader::ShaderParticle shaderProgram;

        unsigned int vertexBufferBillboard;

        unsigned int instanceBufferParticleDynamic;

        unsigned int vaoParticle;

        SceneType sceneType;

        Game() {}
        ~Game() {}

        void init();
        void start();
        void update(float dt);

        static Game* getInstance();
    };
}