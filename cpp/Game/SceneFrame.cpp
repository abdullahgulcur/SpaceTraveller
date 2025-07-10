#include "pch.h"
#include "SceneFrame.h"
#include "Texture2D.h"
#include "FrameBuffer.h"
#include "DrawCommand.h"
#include "Game.h"
#include "GraphicsApi.h"

namespace Game {

    void SceneFrame::init(glm::ivec2 size) {
        this->size = size;

        Engine::Texture::Texture2DConfig config;
        config.width = size.x;
        config.height = size.y;
        config.minFilter = GL_LINEAR;
        config.wrap_s = GL_CLAMP_TO_EDGE;
        config.wrap_t = GL_CLAMP_TO_EDGE;

        Engine::Texture::createTexture2D(this->colorTextureId, config);

        config.format = GL_DEPTH_COMPONENT;
        config.internalFormat = GL_DEPTH_COMPONENT;
        config.type = GL_FLOAT;
        config.minFilter = GL_NEAREST;

        Engine::Texture::createTexture2D(this->depthTextureId, config);

        Engine::FrameBuffer::generateFbo(FBO);
        Engine::FrameBuffer::bindFbo(FBO);
        Engine::FrameBuffer::setFrameBufferTexture(GL_COLOR_ATTACHMENT0, this->colorTextureId);
        Engine::FrameBuffer::setFrameBufferTexture(GL_DEPTH_ATTACHMENT, this->depthTextureId);

        Engine::FrameBuffer::generateRBO(RBO, size);

        if (!Engine::FrameBuffer::frameBufferComplete()) {
            int x = 5;
        }

        Engine::Shader::createShaderFXAA(shaderFXAA);

        Game* game = Game::getInstance();
        planeVAO = game->quadVAO;

    }

    void SceneFrame::activate() {

        Engine::FrameBuffer::bindFbo(FBO);
        glViewport(0, 0, size.x, size.y);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }

    void SceneFrame::postProcess() {

        Engine::FrameBuffer::unbindFbo();
        glViewport(0, 0, size.x, size.y);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        Engine::Shader::updateUniforms(shaderFXAA, colorTextureId, size);
        Engine::DrawCommand::drawQuad(planeVAO);
    }


}