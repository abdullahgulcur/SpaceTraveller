#pragma once

#include "Core.h"

#include "glm.hpp"
#include "Camera.h"
#include "OrbitCameraController.h"

#include "MeshData.h"
#include "ShaderProgram.h"

namespace Game {

    class PlanetScene {
    private:

        Engine::MeshData::MeshData meshData;
        Engine::Shader::PlanetShader shader;
        Engine::Camera::Camera camera;
        OrbitCameraController cameraCtrl;
        unsigned int textureId0;
        unsigned int textureId1;
        unsigned int vao;
        glm::mat4 model;

        /*Engine::MeshData::MeshData planeMeshData;
        Engine::Shader::SimpleShaderProgram planeShader;
        unsigned int planeTextureId;
        unsigned int planeVao;*/

    public:

        PlanetScene() {}
        ~PlanetScene() {}

        void init();
        void update(float dt);
    };
}