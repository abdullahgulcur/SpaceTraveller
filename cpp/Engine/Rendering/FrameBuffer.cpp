#include "pch.h"
#include <GLES3/gl32.h>

#include "FrameBuffer.h"

namespace Engine{

    namespace FrameBuffer{

        void bindFbo(unsigned int fbo){
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        }

        void unbindFbo(){
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void generateFbo(unsigned int& fbo){
            glGenFramebuffers(1, &fbo);
        }

        void generateFbo(unsigned int& fbo, unsigned int textureId, unsigned int attachment){
            generateFbo(fbo);
            bindFbo(fbo);
            setFrameBufferTexture(attachment, textureId);
        }

        void deleteFbo(unsigned int& fbo){
            unbindFbo();
            glDeleteFramebuffers(1, &fbo);
        }

        void setFrameBufferTexture(unsigned int attachment, unsigned int textureId){
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureId, 0);
        }

        bool frameBufferComplete(){
            return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
        }
    }
}
