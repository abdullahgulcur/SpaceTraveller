#include "pch.h"
#include "RenderBuffer.h"
#include "GraphicsApi.h"

namespace Engine {

    RenderBuffer::RenderBuffer() {

    }

    RenderBuffer::~RenderBuffer() {

    }

    void RenderBuffer::generateDepthRbo(glm::ivec2 size) {

        RenderBuffer::generate();
        RenderBuffer::bind();
        RenderBuffer::setStorage(size);
        RenderBuffer::unbind();
    }

    void RenderBuffer::bind() {
        glBindRenderbuffer(GL_RENDERBUFFER, id);
    }

    void RenderBuffer::unbind() {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void RenderBuffer::generate() {
        glGenRenderbuffers(1, &id);
    }

    void RenderBuffer::setStorage(glm::ivec2 size) {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size.x, size.y);
    }

    void RenderBuffer::deleteRbo() {
        glDeleteRenderbuffers(1, &id);
    }

}