#include "pch.h"
#include "Core.h"
#include "FrameBuffer.h"
#include "GraphicsApi.h"

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

        void refreshScreen(){
            Engine::Core* core = Engine::Core::getInstance();
            glViewport(0, 0, core->appSurface.getWidth(), core->appSurface.getHeight());
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

        }
    }
}
