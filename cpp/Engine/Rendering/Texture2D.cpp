#include "pch.h"
#include <GLES3/gl32.h>

#include "Texture2D.h"
#include "FrameBuffer.h"
#include "ShaderProgram.h"
#include "Core.h"
#include "TextureData.h"
#include "DrawCommand.h"

namespace Engine{

    namespace Texture{

        void createTexture2D(unsigned int& textureId, Texture2DConfig& config){
            generateTex(textureId);
            bindTex2D(textureId);
            texImage2D(config.internalFormat, config.format, config.width, config.height, config.type, config.data);
            texParams2D(config.wrap_s, config.wrap_t, config.minFilter, config.magFilter);
            if(!config.data)
                return;
            if(config.minFilter == GL_LINEAR_MIPMAP_LINEAR || config.minFilter == GL_NEAREST_MIPMAP_LINEAR || config.minFilter == GL_NEAREST_MIPMAP_NEAREST || config.minFilter == GL_LINEAR_MIPMAP_NEAREST)
                mipmapTex2D();
        }

        void texImage2D(unsigned int internalFormat, unsigned int format, unsigned int width, unsigned int height, unsigned int type, const void* data){
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
        }

        void texParams2D(unsigned int wrap_s, unsigned int wrap_t, unsigned int minFilter, unsigned int magFilter){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        }

        void mipmapTex2D(unsigned int textureId){
            bindTex2D(textureId);
            mipmapTex2D();
        }

        void mipmapTex2D(){
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void bindTex2D(unsigned int textureId){
            glBindTexture(GL_TEXTURE_2D, textureId);
        }

        void generateTex(unsigned int& textureId){
            glGenTextures(1, &textureId);
        }

        void unbindTex2D(){
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void clearTex(unsigned int& textureId){
            unbindTex2D();
            glDeleteTextures(1, &textureId);
        }

        void setTexSlot2D(unsigned int slot, unsigned int textureId){
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textureId);
        }

        // should be in asset manager, i think
        void generateGalaxyFrameBufferTexture(unsigned int& galaxyTextureId, unsigned int dimension){

//            GLint supported;
//            glGetInternalformativ(GL_RENDERBUFFER, GL_RGBA8, GL_FRAMEBUFFER_RENDERABLE, 1, &supported);

            TextureData2D data("texture/noise.jpg", 1);

            Texture2DConfig noiseTexConfig;
            noiseTexConfig.data = data.data;
            noiseTexConfig.width = data.width;
            noiseTexConfig.height = data.height;
            noiseTexConfig.internalFormat = GL_R8;
            noiseTexConfig.format = GL_RED;

            unsigned int noiseTextureId;
            createTexture2D(noiseTextureId, noiseTexConfig);

            Texture2DConfig galaxyTexConfig;
            galaxyTexConfig.width = dimension;
            galaxyTexConfig.height = dimension;
            galaxyTexConfig.internalFormat = GL_RGBA8;
            galaxyTexConfig.format = GL_RGBA;

            createTexture2D(galaxyTextureId, galaxyTexConfig);

            unsigned int fbo;
            FrameBuffer::generateFbo(fbo, galaxyTextureId, GL_COLOR_ATTACHMENT0);

            if(FrameBuffer::frameBufferComplete())
                int x = 5;

            ShaderProgram shaderProgram("shader/quad.vert", "shader/galaxy.frag");
            shaderProgram.bind();
            shaderProgram.uniform("noiseTexture", 0);

            glViewport(0, 0, dimension, dimension);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT);

            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, noiseTextureId);

            VertexBuffer::VertexBuffer vb = AssetManager::loadQuadMesh();

            unsigned int vao;
            Vao::createQuadMeshVao(vao, vb.bufferId);

            DrawCommand::drawQuad(vao);

            mipmapTex2D(galaxyTextureId);

            VertexBuffer::clear(vb.bufferId);
            Vao::deleteVao(vao);
            shaderProgram.clear();
            clearTex(noiseTextureId);
            FrameBuffer::deleteFbo(fbo);
        }

    }

    Texture2D::Texture2D(std::vector<unsigned char>& buffer, unsigned int width, unsigned int height, unsigned int blockDimension){

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        std::map<unsigned int, unsigned int> types;
        types[4] = GL_COMPRESSED_RGBA_ASTC_4x4;
        types[5] = GL_COMPRESSED_RGBA_ASTC_5x5;
        types[6] = GL_COMPRESSED_RGBA_ASTC_6x6;
        types[8] = GL_COMPRESSED_RGBA_ASTC_8x8;
        types[10] = GL_COMPRESSED_RGBA_ASTC_10x10;
        types[12] = GL_COMPRESSED_RGBA_ASTC_12x12;

        unsigned int internalFormat = types[blockDimension];

        glCompressedTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, buffer.size() - 16, &buffer[0] + 16);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture2D::Texture2D(const void* buffer, unsigned int width, unsigned int height, unsigned int channels){

        unsigned int formats[4] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
        unsigned int format = formats[channels - 1];

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }

}
