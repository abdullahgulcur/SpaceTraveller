#pragma once

#include "Core.h"

#include "glm.hpp"
#include "Camera.h"
#include "CameraController.h"

namespace Game {

    class ObjectScene {
    private:

        Engine::MeshData::MeshData meshData;
        Engine::Shader::SimpleShaderProgram shaderProgram;
        Engine::Camera::Camera camera;
        CameraController cameraCtrl;
        unsigned int textureId;
        unsigned int vao;
        std::vector<glm::mat4> models;
        unsigned int instanceBuffer;

    public:

        ObjectScene() {}
        ~ObjectScene() {}

        void init();
        void update(float dt);
    };
}