#pragma once

#include "glm.hpp"
#include "ShaderProgram.h"

namespace Game {

    class SceneFrame {
    private:

    public:

        glm::ivec2 size;
        unsigned int planeVAO;
        unsigned int colorTextureId;
        unsigned int depthTextureId;
        unsigned int FBO;
        unsigned int RBO;
        Engine::Shader::ShaderFXAA shaderFXAA;

        SceneFrame() {}
        void init(glm::ivec2 size);
        ~SceneFrame() {}
        void activate();
        void postProcess();

    };
}