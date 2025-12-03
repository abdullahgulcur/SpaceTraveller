#pragma once

#include "glm.hpp"
#include "Shader.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"

namespace Game {

    class SceneFrame {
    private:

    public:

        glm::ivec2 size;
        unsigned int planeVAO;
        unsigned int colorTextureId;
        unsigned int depthTextureId;
        //unsigned int FBO;

        Engine::FrameBuffer fbo;
        Engine::RenderBuffer rbo;

        unsigned int RBO;
        Shader::ShaderFXAA shaderFXAA;

        SceneFrame() {}
        void init(glm::ivec2 size);
        ~SceneFrame() {}
        void activate();
        void postProcess();

    };
}