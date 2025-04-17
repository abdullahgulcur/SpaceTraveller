#pragma once

namespace Engine{

    namespace FrameBuffer {

        void bindFbo(unsigned int fbo);
        void unbindFbo();
        void generateFbo(unsigned int& fbo);
        void generateFbo(unsigned int& fbo, unsigned int textureId, unsigned int attachment);
        void deleteFbo(unsigned int& fbo);
        void setFrameBufferTexture(unsigned int attachment, unsigned int textureId);
        bool frameBufferComplete();
    }

}
