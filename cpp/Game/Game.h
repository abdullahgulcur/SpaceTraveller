#pragma once

#include "Core.h"
#include "MeshData.h"
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

        Engine::MeshData::MeshData sphereMeshData;
        Engine::Shader::PlanetShader planetShader;
        Engine::Shader::ShaderSun shaderSun;
        unsigned int perlinTextureId;
        unsigned int macroTextureId;
        unsigned int vaoSphereMesh;


        //TunnelEffectScene tunnelEffectScene;

        Universe universe;

        Engine::ParticleSystem::ParticleTunnel<1024> particleSystem;
        Engine::ParticleSystem::ParticleSolarSystem<256> particleSolarSystems;


        Engine::Camera::Camera camera;
        //Engine::Shader::ShaderParticle shaderProgram;
        Engine::Shader::ShaderParticleSolarSystem shaderParticleSolarSystem;


        unsigned int vertexBufferBillboard;

        unsigned int instanceBufferParticleDynamic;

        //unsigned int vaoParticle;
        unsigned int vaoParticleSolarSystem;

        SceneType sceneType;

        Game() {}
        ~Game() {}

        void init();
        void start();
        void update(float dt);

        static Game* getInstance();
    };
}