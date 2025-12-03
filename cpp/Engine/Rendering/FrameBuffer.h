#pragma once

#include "glm.hpp"

namespace Engine{

    class FrameBuffer {

    private:

        unsigned int id;
        //unsigned int rbo;

    public:

        FrameBuffer();
        ~FrameBuffer();
        //void generateSceneSetup(unsigned int colorTextureId, unsigned int depthTextureId);
        void bind();
        void unbind();
        void generate();
        void attachDepthRbo(unsigned int rbo);
        //void generateRBO(unsigned int& RBO, glm::ivec2 size);
        //void generate(unsigned int textureId, unsigned int attachment);
        void deleteFbo();
        //void setTexture(unsigned int attachment, unsigned int textureId);
        //void setTextures(unsigned int colorTextureId, unsigned int depthTextureId);
        void attachTexColor(unsigned int textureId);
        void attachTexDepth(unsigned int textureId);
        bool isComplete();
        //void refreshScreen();

    };

    //namespace FrameBuffer {

    //    void bindFbo(unsigned int fbo);
    //    void unbindFbo();
    //    void generateFbo(unsigned int& fbo);
    //    void generateRBO(unsigned int& RBO, glm::ivec2 size);
    //    void generateFbo(unsigned int& fbo, unsigned int textureId, unsigned int attachment);
    //    void deleteFbo(unsigned int& fbo);
    //    void setFrameBufferTexture(unsigned int attachment, unsigned int textureId);
    //    bool frameBufferComplete();
    //    void refreshScreen();
    //}

}
